#ifndef TOOLS_H
#define TOOLS_H

/* C++ */
#include <string>
#include <chrono>
#include <vector>

/* SRC */
#include <vec3.h>
#include <pointCloud.h>
#include <material.h>

std::string displayElectricityPrice(int duration);
void linkToCuda(std::vector<PointCloud> scenePointCloud, int width, int height, float ModelViewMatrix[16], float projectionMatrix[16], Vec3 cameraPos);

#endif