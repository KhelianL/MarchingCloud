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