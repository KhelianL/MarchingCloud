#ifndef POINTCLOUD_H
#define POINTCLOUD_H

/* C LIBS */
#include <fstream>
#include <string>
#include <vector>

/* libQGLViewer */
#include <vec.h>

#include <Vec3.h> 


#define M_PI = 3.14159265358979323846

extern "C" struct Material{
    Vec3 AMBIANT_COLOR = Vec3(0,0,0);
    Vec3 DIFFUSE_COLOR= Vec3(0.5,0.5,0.5);
    Vec3 SPECULAR_COLOR= Vec3(0.5,0.5,0.5);

    int SPECULAR_EXPONENT = 32;
    float transparency = 0.0;
    float refractionIndex = 1.0;
};

class PointCloud
{
private:
    std::vector<qglviewer::Vec> positions;
    std::vector<qglviewer::Vec> normals;
    bool isSet = false;

    Material mat;

public:
    // Load-Save
    void setMaterial(Material m);
    void loadPointCloud(const std::string &filename);

    // Transform
    void move(const qglviewer::Vec v);
    void rotate(const float d, const qglviewer::Vec v);
    void scale(const qglviewer::Vec v);

    // Getters
    std::vector<qglviewer::Vec> &getPositions();
    std::vector<qglviewer::Vec> &getNormals();
    Material getMaterial();

    // Draw OpenGL
    void draw();
};

#endif