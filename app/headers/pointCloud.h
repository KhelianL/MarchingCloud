#ifndef POINTCLOUD_H
#define POINTCLOUD_H

/* QT */
#include <QString>

/* C++ */
#include <vector>

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

    bool isSet = false;

public:
    // Load-Reset
    void loadPointCloud(const std::string &filename);
    void reset();

    // Transform
    void move(const Vec3 v);
    void rotate(const float d, const Vec3 v);
    void scale(const Vec3 v);

    // Generate
    void generatePlane(int resolution);
    void generateSphere(int resolution);
    void generateCube(int resolution);
    void generateTorus(int resolution);
    void generateRabbit(int resolution);


    // Getters
    std::vector<Vec3> &getPositions();
    std::vector<Vec3> &getNormals();
    Material &getMaterial();

    // Setters
    void setMaterial(Material m);

    // Draw OpenGL
    void draw();
};

#endif
