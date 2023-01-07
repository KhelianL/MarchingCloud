#ifndef SCENE_H
#define SCENE_H

/* C LIBS */
#include <vector>

/* SRC CUDA */
#include <pointCloud.h>

class Scene
{
private:
    std::vector<PointCloud> listPointCloud;

public:
    Scene();

    void draw();
    void init();

    std::vector<PointCloud> &getListPointCloud();

    void generateImport(const std::string &filename);
};

#endif