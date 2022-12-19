/* SRC */
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
            this->positions.push_back(qglviewer::Vec(pn[i], pn[i + 1], pn[i + 2]));
            this->normals.push_back(qglviewer::Vec(pn[i + 3], pn[i + 4], pn[i + 5]));
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

void PointCloud::move(const qglviewer::Vec v)
{
    if (this->isSet)
    {
        for (unsigned int i = 0, sizeV = this->positions.size(); i < sizeV; i++)
        {
            this->positions[i] += v;
        }
    }
}
void PointCloud::rotate(const float d, const qglviewer::Vec v)
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
            qglviewer::Vec rotatedVector;
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
void PointCloud::scale(const qglviewer::Vec v)
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

std::vector<qglviewer::Vec> &PointCloud::getPositions()
{
    return this->positions;
}
std::vector<qglviewer::Vec> &PointCloud::getNormals()
{
    return this->normals;
}

void PointCloud::draw()
{
    if (this->isSet)
    {
        glBegin(GL_POINTS);
        for (unsigned int i = 0, sizeV = this->positions.size(); i < sizeV; i++)
        {
            glVertex3fv(this->positions[i]);
            glNormal3fv(this->normals[i]);
            glColor3f(1.0, 1.0, 1.0);
        }
        glEnd();
    }
}

void PointCloud::setMaterial(Material m){
    this->mat = m;
}

Material PointCloud::getMaterial(){
    return this->mat;
}

void PointCloud::generateCornellBox(int resolution) {
    this->isSet = true;

  // Taille de la boîte de Cornell
  const float boxSize = 5.0f;

  // Nombre de points par ligne
  const int numPointsPerLine = resolution + 1;

  // Étape de génération des points
  const float step = 2.0f * boxSize / resolution;

  // Création des points de la boîte
  for (int i = 0; i < numPointsPerLine; ++i) {
    for (int j = 0; j < numPointsPerLine; ++j) {
      // Face avant
    //   this->positions.push_back({-boxSize + i * step,  boxSize - j * step,  boxSize});
    //   this->normals.push_back({0.0f, 0.0f, 1.0f});
      // Face arrière
      this->positions.push_back({ boxSize - i * step,  boxSize - j * step, -boxSize});
      this->normals.push_back({0.0f, 0.0f, -1.0f});
      // Face gauche
      this->positions.push_back({-boxSize,  boxSize - i * step, -boxSize + j * step});
      this->normals.push_back({-1.0f, 0.0f, 0.0f});
      // Face droite
      this->positions.push_back({ boxSize,  boxSize - i * step,  boxSize - j * step});
      this->normals.push_back({1.0f, 0.0f, 0.0f});
      // Face haut
      this->positions.push_back({-boxSize + i * step,  boxSize, -boxSize + j * step});
      this->normals.push_back({0.0f, 1.0f, 0.0f});
      // Face bas
      this->positions.push_back({-boxSize + i * step, -boxSize,  boxSize - j * step});
      this->normals.push_back({0.0f, -1.0f, 0.0f});
    }
  }
}

void PointCloud::addSphere(float centerX, float centerY, float centerZ, float radius, int resolution) {
    this->isSet = true;
    const int numTheta = resolution;
    const int numPhi = 2 * resolution;

    for (int i = 0; i < numTheta; ++i) {
        for (int j = 0; j < numPhi; ++j) {
        // Calcul des angles de la sphère
        const float theta = i * M_PI / numTheta;
        const float phi = j * 2 * M_PI / numPhi;

        // Calcul des coordonnées du point sur la sphère
        const float x = centerX + radius * sinf(theta) * cosf(phi);
        const float y = centerY + radius * sinf(theta) * sinf(phi);
        const float z = centerZ + radius * cosf(theta);

        // Calcul et normalisation de la normale
        const float nx = x - centerX;
        const float ny = y - centerY;
        const float nz = z - centerZ;
        const float norm = sqrtf(nx * nx + ny * ny + nz * nz);
        const qglviewer::Vec normal = {nx / norm, ny / norm, nz / norm};

        // Ajout du point et de sa normale au vecteur
        positions.push_back({x, y, z});
        normals.push_back(normal);
        }
    }
}