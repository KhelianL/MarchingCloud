#ifndef POINTCLOUD_H
#define POINTCLOUD_H

/* QT */
#include <QString>

/* C++ */
#include <vector>
#include <random> // mt19937
#include <ctime>  // time(nullptr)

/* GLUT */
#include <GL/glut.h>

/* SRC */
#include <material.h>
#include <vec3.h>

#define M_PI 3.14159265358979323846

class PointCloud
{
private:
    std::vector<Vec3> positions;
    std::vector<Vec3> normals;
    Material material;

    Vec3 minAABB;
    Vec3 maxAABB;

    bool isSelected = false;

    bool isSet = false;

public:
    // Load-Reset
    void loadPointCloud(const std::string &filename);

    // Transform
    void move(const Vec3 &v);
    void rotate(const float &d, const Vec3 &v);
    void scale(const Vec3 &v);

    // Generate
    void generatePlane(const int &resolution);
    void generateSphere(const int &resolution);
    void generateCube(const int &resolution);
    void generateTorus(const int &resolution);

    // AABB
    void computeAABB();
    Vec3 &getMinAABB();
    Vec3 &getMaxAABB();

    // Decimate
    void decimate(const float &keepingPart);

    // Getters
    std::vector<Vec3> &getPositions();
    std::vector<Vec3> &getNormals();
    Material &getMaterial();

    // Setters
    void setMaterial(const Material &m);
    void setIsSelected(const bool &b);

    // Draw OpenGL
    void draw();
};

#endif
