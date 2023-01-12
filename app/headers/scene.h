#ifndef SCENE_H
#define SCENE_H

/* C++ */
#include <vector>
#include <fstream>
#include <string>

/* SRC */
#include <pointCloud.h>
#include <popupCreate.h>

class Scene
{
private:
    std::vector<PointCloud> listPointCloud;

public:
    Scene();

    void draw();
    void init();

    std::vector<PointCloud> &getListPointCloud();
    PointCloud &getPointCloudAtIndex(const int &index);
    void removePointCloudAtIndex(const int &index);
    void addPointCloud(const PointCloud &p);

    void generateImport(const std::string &filename, const float &decimate);
    void generatePrimitive(const PointCloudType &type, const int &resolution);
};

#endif