#include <pointCloud.h>

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
        this->isSet = true;
    }
}

void PointCloud::reset()
{
    this->positions.clear();
    this->normals.clear();
}

void PointCloud::move(const Vec3 v)
{
    if (this->isSet)
    {
        for (unsigned int i = 0, sizeV = this->positions.size(); i < sizeV; i++)
        {
            this->positions[i] += v;
        }
    }
}
void PointCloud::rotate(const float d, const Vec3 v)
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
    }
}
void PointCloud::scale(const Vec3 v)
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
    }
}

std::vector<Vec3> &PointCloud::getPositions()
{
    return this->positions;
}
std::vector<Vec3> &PointCloud::getNormals()
{
    return this->normals;
}
Material &PointCloud::getMaterial()
{
    return this->material;
}

void PointCloud::setMaterial(Material m)
{
    this->material = m;
}

void PointCloud::generatePlane(int resolution)
{
    this->reset();

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

    this->isSet = true;
}
void PointCloud::generateSphere(int resolution)
{
    this->reset();

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

    this->isSet = true;
}
void PointCloud::generateCube(int resolution)
{
    this->reset();

    // Création du cube
    for (int i = 0; i < resolution; ++i)
    {
        for (int j = 0; j < resolution; ++j)
        {
            for (int k = 0; k < resolution; ++k)
            {
                if (i == 0 || i == resolution - 1 || j == 0 || j == resolution - 1 || k == 0 || k == resolution - 1)
                {
                    Vec3 position = Vec3(i / (float)(resolution - 1) - 0.5, j / (float)(resolution - 1) - 0.5, k / (float)(resolution - 1) - 0.5);
                    position *= 2;
                    this->positions.push_back(position);

                    Vec3 normal = Vec3(i - resolution / 2, j - resolution / 2, k - resolution / 2);
                    normal.normalize();
                    this->normals.push_back(normal);
                }
            }
        }
    }

    this->isSet = true;
}
void PointCloud::generateTorus(int resolution)
{
    this->reset();

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
            this->positions.push_back({x, y, z});
            this->normals.push_back(normal);
        }
    }

    this->isSet = true;
}

void PointCloud::generateRabbit(int resolution)
{
    int numLevels = 5;
        this->reset();

    for (int i = 0; i < numLevels; ++i)
    {
        const int numHeight = resolution;
        const int numRadius = 2 * resolution;

        const float height = i / (numLevels - 1.0f);
        const float radius = 0.1f + 0.9f * height;

        for (int j = 0; j < numHeight; ++j)
        {
            for (int k = 0; k < numRadius; ++k)
            {
                // Calcul de l'angle radial
                const float theta = k * 2 * M_PI / numRadius;

                // Calcul des coordonnées du point sur le cône
                // const float x = radius * cos(theta);
                // const float y = radius * sin(theta);
                // const float z = j / (numHeight - 1.0f) + i;

                const float x = cos(radius) * (height - j) / height;
                const float y = sin(radius) * (height - j) / height;
                const float z = j / (height - 1.0f) + i;

                // Calcul et normalisation de la normale
                const float norm = sqrtf(x * x + y * y + z * z);
                const Vec3 normal = {x / norm, y / norm, z / norm};

                // Ajout du point et de sa normale au vecteur
                this->positions.push_back({x, y, z});
                this->normals.push_back(normal);
            }
        }
    }

    this->isSet = true;
}

void PointCloud::draw()
{
    if (this->isSet)
    {
        glBegin(GL_POINTS);
        for (unsigned int i = 0, sizeV = this->positions.size(); i < sizeV; i++)
        {
            glVertex3f(this->positions[i][0], this->positions[i][1], this->positions[i][2]);
            glNormal3f(this->normals[i][0], this->normals[i][1], this->normals[i][2]);
            glColor3f(1.0, 1.0, 1.0);
        }
        glEnd();
    }
}
