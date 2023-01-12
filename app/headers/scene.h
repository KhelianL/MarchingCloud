#ifndef SCENE_H
#define SCENE_H

/* C LIBS */
#include <vector>
#include <fstream>
#include <string>

/* SRC CUDA */
#include <pointCloud.h>
#include <popupWindow.h>

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

    void generateImport(const std::string &filename, const float &decimate);
    void generatePrimitive(const PopupType &type, const int &resolution);

    void sceneParserJSON(const std::string &filename);
};

#endif