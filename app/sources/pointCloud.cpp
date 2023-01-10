#include <pointCloud.h>

// Getters
std::vector<Vec3> &PointCloud::getPositions() { return this->positions; }
std::vector<Vec3> &PointCloud::getNormals() { return this->normals; }
Material &PointCloud::getMaterial() { return this->material; }
Vec3 &PointCloud::getRelativePosition() { return this->relativePosition; }
Vec3 &PointCloud::getRelativeRotation() { return this->relativeRotation; }
Vec3 &PointCloud::getRelativeScale() { return this->relativeScale; }

// Setters
void PointCloud::setMaterial(const Material &m) { this->material = m; }
void PointCloud::setIsSelected(const bool &b) { this->isSelected = b; }

// Transform
void PointCloud::move(const Vec3 &v)
{
    if (this->isSet)
    {
        this->relativePosition += v;
        for (unsigned int i = 0, sizeV = this->positions.size(); i < sizeV; i++)
        {
            this->positions[i] += this->relativePosition;
        }
        this->minAABB += this->relativePosition;
        this->maxAABB += this->relativePosition;
    }
}
void PointCloud::rotate(const float &d, const Vec3 &v)
{
    if (this->isSet)
    {
        // Création de la matrice de rotation
        float c = cos(d);
        float s = sin(d);
        float x = v[0];
        float y = v[1];
        float z = v[2];
        float x2 = x * x;
        float y2 = y * y;
        float z2 = z * z;

        float rotationMatrix[3][3] = {
            {c + x2 * (1 - c), x * y * (1 - c) - z * s, x * z * (1 - c) + y * s},
            {y * x * (1 - c) + z * s, c + y2 * (1 - c), y * z * (1 - c) - x * s},
            {z * x * (1 - c) - y * s, z * y * (1 - c) + x * s, c + z2 * (1 - c)}};

        // Appliquer la rotation à chaque vecteur de positions
        for (unsigned int i = 0, sizeV = this->positions.size(); i < sizeV; i++)
        {
            Vec3 rotatedVector;
            for (int j = 0; j < 3; j++)
            {
                rotatedVector[j] = 0;
                for (int k = 0; k < 3; k++)
                {
                    rotatedVector[j] += rotationMatrix[j][k] * this->positions[i][k];
                }
            }
            this->positions[i] = rotatedVector;
        }
        this->computeAABB();
    }
}
void PointCloud::scale(const Vec3 &v)
{
    if (this->isSet)
    {
        for (unsigned int i = 0, sizeV = this->positions.size(); i < sizeV; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                this->positions[i][j] = this->positions[i][j] * v[j];
            }
        }
        this->computeAABB();
    }
}

// Generation
void PointCloud::loadPointCloud(const std::string &filename)
{
    FILE *in = fopen(filename.c_str(), "rb");
    if (in == NULL)
    {
        std::cout << filename << " is not a valid PN file." << std::endl;
        return;
    }

    unsigned int surfelSize = 6;
    size_t READ_BUFFER_SIZE = 1000;
    float *pn = new float[surfelSize * READ_BUFFER_SIZE];

    while (!feof(in))
    {
        unsigned numOfPoints = fread(pn, 4, surfelSize * READ_BUFFER_SIZE, in);
        for (unsigned int i = 0; i < numOfPoints; i += surfelSize)
        {
            this->positions.push_back(Vec3(pn[i], pn[i + 1], pn[i + 2]));
            this->normals.push_back(Vec3(pn[i + 3], pn[i + 4], pn[i + 5]));
        }

        if (numOfPoints < surfelSize * READ_BUFFER_SIZE)
            break;
    }

    fclose(in);
    delete[] pn;

    // Verification
    if (this->positions.size() != this->normals.size())
    {
        std::cout << "The pointset does not contain the same number of points and normals." << std::endl;
        this->positions.clear();
        this->normals.clear();
        return;
    }
    else
    {
        this->computeAABB();
        this->setMaterial(MaterialType::Custom);
        this->isSet = true;
    }
}
void PointCloud::generatePlane(const int &resolution)
{
    // Calcule le nombre de sommets nécessaires pour le plan
    const int numVertices = (resolution + 1) * (resolution + 1);
    this->positions.resize(numVertices);
    this->normals.resize(numVertices);

    // Initialise les sommets et les normales
    for (int i = 0; i <= resolution; ++i)
    {
        for (int j = 0; j <= resolution; ++j)
        {
            // Calcule les coordonnées du sommet (x, y) en fonction de la résolution
            float x = (float)i / resolution * 2.0 - 1.0;
            float y = (float)j / resolution * 2.0 - 1.0;

            // Affecte les coordonnées du sommet et la normale (0, 0, 1)
            this->positions[i * (resolution + 1) + j] = Vec3(x, y, 0.0);
            this->normals[i * (resolution + 1) + j] = Vec3(0.0, 0.0, 1.0);
        }
    }

    this->computeAABB();
    this->isSet = true;
}
void PointCloud::generateSphere(const int &resolution)
{
    // TODO : REVOIR LA GEN D'UNE SPHERE!
    const int numTheta = resolution;
    const int numPhi = 2 * resolution;

    for (int i = 0; i < numTheta; ++i)
    {
        for (int j = 0; j < numPhi; ++j)
        {
            // Calcul des angles de la sphère
            const float theta = i * M_PI / numTheta;
            const float phi = j * 2 * M_PI / numPhi;

            // Calcul des coordonnées du point sur la sphère
            const float x = sinf(theta) * cosf(phi);
            const float y = sinf(theta) * sinf(phi);
            const float z = cosf(theta);

            // Calcul et normalisation de la normale
            const float norm = sqrtf(x * x + y * y + z * z);
            const Vec3 normal = {x / norm, y / norm, z / norm};

            // Ajout du point et de sa normale au vecteur
            this->positions.push_back({x, y, z});
            this->normals.push_back(normal);
        }
    }

    this->computeAABB();
    this->isSet = true;
}
void PointCloud::generateCube(const int &resolution)
{
    const int numLoop = resolution + 1;
    // Création du cube
    for (int i = 0; i < numLoop; ++i)
    {
        for (int j = 0; j < numLoop; ++j)
        {
            for (int k = 0; k < numLoop; ++k)
            {
                if (i == 0 || i == numLoop - 1 || j == 0 || j == numLoop - 1 || k == 0 || k == numLoop - 1)
                {
                    Vec3 position = Vec3(i / (float)(numLoop - 1) - 0.5, j / (float)(numLoop - 1) - 0.5, k / (float)(numLoop - 1) - 0.5);
                    position *= 2;
                    this->positions.push_back(position);

                    Vec3 normal = Vec3(i - numLoop / 2, j - numLoop / 2, k - numLoop / 2);
                    normal.normalize();
                    this->normals.push_back(normal);
                }
            }
        }
    }

    this->computeAABB();
    this->isSet = true;
}
void PointCloud::generateTorus(const int &resolution)
{
    const int numTheta = resolution;
    const int numPhi = 2 * resolution;

    for (int i = 0; i < numTheta; ++i)
    {
        for (int j = 0; j < numPhi; ++j)
        {
            // Calcul des angles polaires
            const float theta = i * 2 * M_PI / numTheta;
            const float phi = j * 2 * M_PI / numPhi;

            // Calcul des coordonnées du point sur le tore
            const float x = (2 + cos(theta)) * cos(phi);
            const float y = (2 + cos(theta)) * sin(phi);
            const float z = sin(theta);

            // Calcul et normalisation de la normale
            const float norm = sqrtf(x * x + y * y + z * z);
            const Vec3 normal = {x / norm, y / norm, z / norm};

            // Ajout du point et de sa normale au vecteur
            Vec3 pos = Vec3(x, y, z) / 3;
            this->positions.push_back(pos);
            this->normals.push_back(normal);
        }
    }

    this->computeAABB();
    this->isSet = true;
}

// Decimate
void PointCloud::decimate(const float &keepingPart)
{
    // On commence par vérifier que la valeur de keepingPart est correcte
    if (keepingPart <= 0 || keepingPart > 1)
    {
        std::cerr << "Error: keepingPart must be a value between 0 and 1" << std::endl;
        return;
    }

    // On utilise un générateur de nombres aléatoires pour sélectionner les points à conserver
    std::mt19937 randomGenerator(time(nullptr));
    std::uniform_real_distribution<float> distribution(0.0f, 1.0f);

    // On parcours chaque point et on décide s'il doit être conservé ou non
    std::vector<Vec3> newPositions;
    std::vector<Vec3> newNormals;
    for (int i = 0; i < this->positions.size(); i++)
    {
        float randomNumber = distribution(randomGenerator);
        if (randomNumber <= keepingPart)
        {
            // On conserve le point et les informations associées
            newPositions.push_back(this->positions[i]);
            newNormals.push_back(this->normals[i]);
        }
    }

    this->positions.resize(newPositions.size());
    this->normals.resize(newNormals.size());

    for (int i = 0; i < newPositions.size(); i++)
    {
        this->positions[i] = newPositions[i];
        this->normals[i] = newNormals[i];
    }
}

// AABB
void PointCloud::computeAABB()
{
    float minX = std::numeric_limits<float>::max();
    float minY = std::numeric_limits<float>::max();
    float minZ = std::numeric_limits<float>::max();
    float maxX = -std::numeric_limits<float>::max();
    float maxY = -std::numeric_limits<float>::max();
    float maxZ = -std::numeric_limits<float>::max();

    for (int i = 0, maxSize = this->positions.size(); i < maxSize; i++)
    {
        minX = std::min(minX, this->positions[i].getX());
        minY = std::min(minY, this->positions[i].getY());
        minZ = std::min(minZ, this->positions[i].getZ());
        maxX = std::max(maxX, this->positions[i].getX());
        maxY = std::max(maxY, this->positions[i].getY());
        maxZ = std::max(maxZ, this->positions[i].getZ());
    }

    this->minAABB = Vec3(minX, minY, minZ);
    this->maxAABB = Vec3(maxX, maxY, maxZ);
}
Vec3 &PointCloud::getMinAABB()
{
    return this->minAABB;
}
Vec3 &PointCloud::getMaxAABB()
{
    return this->maxAABB;
}

// Draw
void PointCloud::draw()
{
    if (this->isSet)
    {
        glBegin(GL_POINTS);
        for (unsigned int i = 0, sizeV = this->positions.size(); i < sizeV; i++)
        {
            glVertex3f(this->positions[i][0], this->positions[i][1], this->positions[i][2]);
            glNormal3f(this->normals[i][0], this->normals[i][1], this->normals[i][2]);
            if (this->isSelected)
            {
                glColor3f(1.0, 0.0, 0.0);
            }
            else
            {
                glColor3f(1.0, 1.0, 1.0);
            }
        }
        glEnd();
    }
}
