#ifndef POINTCLOUD_H
#define POINTCLOUD_H

/* QT */
#include <QString>
#include <QMatrix4x4>

/* C++ */
#include <vector>
#include <random> // mt19937
#include <ctime>  // time(nullptr)
#include <string>

/* GLUT */
#include <GL/glut.h>

/* SRC */
#include <material.h>
#include <vec3.h>

#define M_PI 3.14159265358979323846

enum class PointCloudType
{
    IMPORT,
    PLANE,
    SPHERE,
    CUBE,
    TORUS
};
constexpr static const char *PointCloudTable[] = {
    "IMPORT",
    "PLANE",
    "SPHERE",
    "CUBE",
    "TORUS"};

std::string getPointCloudTypeToString(const PointCloudType &type);

class PointCloud
{
private:
    // Define PointCloud
    std::vector<Vec3> positions;
    std::vector<Vec3> normals;
    Material material;

    // Transformations
    QMatrix4x4 modelMatrix;
    Vec3 relativePosition = Vec3(0.0f, 0.0f, 0.0f);
    Vec3 relativeRotation = Vec3(0.0f, 0.0f, 0.0f);
    Vec3 relativeScale = Vec3(1.0f, 1.0f, 1.0f);

    // RayCast AABB
    Vec3 minAABB;
    Vec3 maxAABB;
    bool isSelected = false;

    // Assume that PointCloud is correctly init
    bool isSet = false;

    // PointCloud data save
    PointCloudType type;
    int resolution;

public:
    // Getters
    std::vector<Vec3> &getPositions();
    std::vector<Vec3> &getNormals();
    Material &getMaterial();
    Vec3 &getRelativePosition();
    Vec3 &getRelativeRotation();
    Vec3 &getRelativeScale();
    QMatrix4x4 &getModelMatrix();
    PointCloudType &getPointCloudType();
    int &getResolution();

    // Setters
    void setMaterial(const Material &m);
    void setIsSelected(const bool &b);

    // Transform Relative
    void relativeMoveX(const float &v);
    void relativeMoveY(const float &v);
    void relativeMoveZ(const float &v);
    void relativeRotateX(const float &v);
    void relativeRotateY(const float &v);
    void relativeRotateZ(const float &v);
    void relativeScaleX(const float &v);
    void relativeScaleY(const float &v);
    void relativeScaleZ(const float &v);

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

    // Update
    void updateMatrix();

    // Draw OpenGL
    void draw();
};

#endif
