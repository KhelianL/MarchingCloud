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
}

void PointCloud::savePointCloud(const std::string &filename)
{
    int sizeV = this->positions.size();
    int sizeN = this->normals.size();
    if (sizeV != sizeN)
    {
        std::cout << "The pointset you are trying to save does not contain the same number of points and normals." << std::endl;
        return;
    }
    FILE *outfile = fopen(filename.c_str(), "wb");
    if (outfile == NULL)
    {
        std::cout << filename << " is not a valid PN file." << std::endl;
        return;
    }
    for (unsigned int pIt = 0; pIt < sizeV; ++pIt)
    {
        fwrite(&(this->positions[pIt]), sizeof(float), 3, outfile);
        fwrite(&(this->normals[pIt]), sizeof(float), 3, outfile);
    }
    fclose(outfile);
}

void PointCloud::draw()
{
    int sizeV = this->positions.size();
    int sizeN = this->normals.size();
    if (sizeV != sizeN)
    {
        std::cout << "The pointset does not contain the same number of points and normals." << std::endl;
        return;
    }

    glBegin(GL_POINTS);
    for (int i = 0; i < sizeV; i++)
    {
        glVertex3fv(this->positions[i]);
        glNormal3fv(this->normals[i]);
        glColor3f(1.0, 1.0, 1.0);
    }
    glEnd();
}

void PointCloud::print()
{
    for (int i = 0; i < this->positions.size(); i++)
    {
        std::cout << this->positions[i] << " ";
    }
    std::cout << std::endl;
}