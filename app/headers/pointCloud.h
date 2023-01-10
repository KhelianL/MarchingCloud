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

    Vec3 relativePosition = Vec3(0.0f, 0.0f, 0.0f);
    Vec3 relativeRotation = Vec3(0.0f, 0.0f, 0.0f);
    Vec3 relativeScale = Vec3(1.0f, 1.0f, 1.0f);

    Vec3 minAABB;
    Vec3 maxAABB;

    bool isSelected = false;

    bool isSet = false;

public:
    // Getters
    std::vector<Vec3> &getPositions();
    std::vector<Vec3> &getNormals();
    Material &getMaterial();
    Vec3 &getRelativePosition();
    Vec3 &getRelativeRotation();
    Vec3 &getRelativeScale();

    // Setters
    void setMaterial(const Material &m);
    void setIsSelected(const bool &b);

    // Transform
    void move(const Vec3 &v);
    void rotate(const float &d, const Vec3 &v);
    void scale(const Vec3 &v);

    // Generate
    void loadPointCloud(const std::string &filename);
    void generatePlane(const int &resolution);
    void generateSphere(const int &resolution);
    void generateCube(const int &resolution);
    void generateTorus(const int &resolution);

    // Decimate
    void decimate(const float &keepingPart);

    // AABB
    void computeAABB();
    Vec3 &getMinAABB();
    Vec3 &getMaxAABB();

    // Draw OpenGL
    void draw();
};

#endif
