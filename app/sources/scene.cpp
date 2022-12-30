#include <scene.h>

Scene::Scene()
{
    this->init();
}

void Scene::draw()
{
    int size = this->listPointCloud.size();
    for (int i = 0; i < size; i++)
        this->listPointCloud[i].draw();
}

void Scene::init()
{
    /*
    PointCloud dino1, dino2, dino3;
    dino1.loadPointCloud("dataPointsets/dino.pn");
    dino2.loadPointCloud("dataPointsets/dino_subsampled.pn");
    dino3.loadPointCloud("dataPointsets/dino_subsampled_extreme.pn");
    dino1.move({-0.5, 0.0, 0.0});
    dino3.move({0.5, 0.0, 0.0});
    this->listPointCloud.push_back(dino1);
    this->listPointCloud.push_back(dino2);
    this->listPointCloud.push_back(dino3);
    */

    PointCloud boule;
    boule.addSphere(0, 0, 0, 1, 50);
    this->listPointCloud.push_back(boule);
}

std::vector<PointCloud> &Scene::getListPointCloud()
{
    return this->listPointCloud;
}