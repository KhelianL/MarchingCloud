#include <pointCloud.h>

std::string getPointCloudTypeToString(const PointCloudType &type) { return PointCloudTable[static_cast<uint32_t>(type)]; }

// Getters
std::vector<Vec3> &PointCloud::getPositions() { return this->positions; }
std::vector<Vec3> &PointCloud::getNormals() { return this->normals; }
Material &PointCloud::getMaterial() { return this->material; }
Vec3 &PointCloud::getRelativePosition() { return this->relativePosition; }
Vec3 &PointCloud::getRelativeRotation() { return this->relativeRotation; }
Vec3 &PointCloud::getRelativeScale() { return this->relativeScale; }
QMatrix4x4 &PointCloud::getModelMatrix() { return this->modelMatrix; }
PointCloudType &PointCloud::getPointCloudType() { return this->type; }
int &PointCloud::getResolution() { return this->resolution; }

// Setters
void PointCloud::setMaterial(const Material &m) { this->material = m; }
void PointCloud::setIsSelected(const bool &b) { this->isSelected = b; }

// Transform Relative for PointCloud
void PointCloud::relativeMoveX(const float &v)
{
    this->relativePosition.setX(v);
    this->updateMatrix();
    this->computeAABB();
}
void PointCloud::relativeMoveY(const float &v)
{
    this->relativePosition.setY(v);
    this->updateMatrix();
    this->computeAABB();
}
void PointCloud::relativeMoveZ(const float &v)
{
    this->relativePosition.setZ(v);
    this->updateMatrix();
    this->computeAABB();
}
void PointCloud::relativeRotateX(const float &v)
{
    this->relativeRotation.setX(v);
    this->updateMatrix();
    this->computeAABB();
}
void PointCloud::relativeRotateY(const float &v)
{
    this->relativeRotation.setY(v);
    this->updateMatrix();
    this->computeAABB();
}
void PointCloud::relativeRotateZ(const float &v)
{
    this->relativeRotation.setZ(v);
    this->updateMatrix();
    this->computeAABB();
}
void PointCloud::relativeScaleX(const float &v)
{
    this->relativeScale.setX(v);
    this->updateMatrix();
    this->computeAABB();
}
void PointCloud::relativeScaleY(const float &v)
{
    this->relativeScale.setY(v);
    this->updateMatrix();
    this->computeAABB();
}
void PointCloud::relativeScaleZ(const float &v)
{
    this->relativeScale.setZ(v);
    this->updateMatrix();
    this->computeAABB();
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
        this->updateMatrix();
        this->computeAABB();
        this->setMaterial(Material(MaterialType::Custom));
        this->isSet = true;
        this->type = PointCloudType::IMPORT;
        this->resolution = -1;
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

    this->updateMatrix();
    this->computeAABB();
    this->isSet = true;
    this->type = PointCloudType::PLANE;
    this->resolution = resolution;
}
void PointCloud::generateSphere(const int &resolution)
{
    const int M = resolution + 1;
    const int N = resolution + 1;

    // Vertices
    for (int i = 0; i <= N; i++)
    {
        float PHI = M_PI * double(i) / double(N);
        for (int j = 0; j <= M; j++)
        {
            float THETA = 2 * M_PI * double(j) / double(M);
            this->positions.push_back(Vec3(sin(PHI) * cos(THETA), cos(PHI), sin(PHI) * sin(THETA)));
        }
    }

    // Normals
    for (int i = 0; i < (int)this->positions.size(); i++)
    {
        this->normals.push_back(Vec3(this->positions[i][0], this->positions[i][1], this->positions[i][2]));
    }

    this->updateMatrix();
    this->computeAABB();
    this->isSet = true;
    this->type = PointCloudType::SPHERE;
    this->resolution = resolution;
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

    this->updateMatrix();
    this->computeAABB();
    this->isSet = true;
    this->type = PointCloudType::CUBE;
    this->resolution = resolution;
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

            // Calcul de la normale
            const float nx = x * cos(theta) - y * sin(theta);
            const float ny = x * sin(theta) + y * cos(theta);
            const float nz = z;

            // Normalisation de la normale
            const float norm = sqrtf(nx * nx + ny * ny + nz * nz);
            const Vec3 normal = {nx / norm, ny / norm, nz / norm};

            // Ajout du point et de sa normale au vecteur
            Vec3 pos = Vec3(x, y, z) / 3;
            this->positions.push_back(pos);
            this->normals.push_back(normal);
        }
    }

    this->updateMatrix();
    this->computeAABB();
    this->isSet = true;
    this->type = PointCloudType::TORUS;
    this->resolution = resolution;
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
        Vec3 tmpVec = Vec3::multMat4(this->modelMatrix.data(), this->positions[i]);
        minX = std::min(minX, tmpVec.getX());
        minY = std::min(minY, tmpVec.getY());
        minZ = std::min(minZ, tmpVec.getZ());
        maxX = std::max(maxX, tmpVec.getX());
        maxY = std::max(maxY, tmpVec.getY());
        maxZ = std::max(maxZ, tmpVec.getZ());
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

// Update
void PointCloud::updateMatrix()
{
    // Initialise la matrice de transformation
    this->modelMatrix.setToIdentity();

    // Applique une translation
    this->modelMatrix.translate(relativePosition[0], relativePosition[1], relativePosition[2]);

    // Applique une rotation
    this->modelMatrix.rotate(relativeRotation[0], 1.0, 0.0, 0.0);
    this->modelMatrix.rotate(relativeRotation[1], 0.0, 1.0, 0.0);
    this->modelMatrix.rotate(relativeRotation[2], 0.0, 0.0, 1.0);

    // Applique une échelle
    this->modelMatrix.scale(relativeScale[0], relativeScale[1], relativeScale[2]);
}

// Draw
void PointCloud::draw()
{
    if (this->isSet)
    {
        glMultMatrixf(this->modelMatrix.data());

        // DrawPoints
        glBegin(GL_POINTS);
        for (unsigned int i = 0, sizeV = this->positions.size(); i < sizeV; i++)
        {
            glVertex3f(this->positions[i][0], this->positions[i][1], this->positions[i][2]);
            glNormal3f(this->normals[i][0], this->normals[i][1], this->normals[i][2]);
            if (this->isSelected)
            {
                glColor3f(0.5, 1.0, 0.5);
            }
            else
            {
                glColor3f(1.0, 1.0, 1.0);
            }
        }
        glEnd();

        // DrawNormals
        /*
        if (this->isSelected)
        {
            glBegin(GL_LINES);
            for (unsigned int i = 0, sizeV = this->positions.size(); i < sizeV; i++)
            {
                glVertex3f(this->positions[i][0], this->positions[i][1], this->positions[i][2]);
                glVertex3f(this->positions[i][0] + this->normals[i][0] * 0.05f, this->positions[i][1] + this->normals[i][1] * 0.05f, this->positions[i][2] + this->normals[i][2] * 0.05f);
                glColor3f(1.0, 0.0, 0.0);
            }
            glEnd();
        }
        */

        glFlush();
        glMultMatrixf(this->modelMatrix.inverted().data());
    }
}
