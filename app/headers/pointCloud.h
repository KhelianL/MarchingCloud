#ifndef POINTCLOUD_H
#define POINTCLOUD_H

/* C LIBS */
#include <fstream>
#include <string>
#include <vector>

/* libQGLViewer */
#include <vec.h>

#define M_PI = 3.14159265358979323846

class PointCloud
{
private:
    std::vector<qglviewer::Vec> positions;
    std::vector<qglviewer::Vec> normals;
    bool isSet = false;

public:
    // Load-Save
    void loadPointCloud(const std::string &filename);

    // Transform
    void move(const qglviewer::Vec v);
    void rotate(const float d, const qglviewer::Vec v);
    void scale(const qglviewer::Vec v);

    // Getters
    std::vector<qglviewer::Vec> &getPositions();
    std::vector<qglviewer::Vec> &getNormals();

    // Draw OpenGL
    void draw();
};

#endif