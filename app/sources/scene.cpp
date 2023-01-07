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
    PointCloud dino1;
    dino1.loadPointCloud("dataPointsets/dino.pn");
    dino1.move({-0.5, 0.0, 0.0});
    this->listPointCloud.push_back(dino1);

    PointCloud dino2;
    dino2.loadPointCloud("dataPointsets/dino_subsampled.pn");
    this->listPointCloud.push_back(dino2);
    */


    PointCloud dino3;
    dino3.loadPointCloud("dataPointsets/dino_subsampled_extreme.pn");
    dino3.move({2.0, 0.0, 0.0});
    dino3.setMaterial(Material(MaterialType::Gold));
    this->listPointCloud.push_back(dino3);
    

    PointCloud boule;
    boule.addSphere(0, 0, 0, 1, 50);
    dino3.setMaterial(Material(MaterialType::Mirror));
    this->listPointCloud.push_back(boule);
}

std::vector<PointCloud> &Scene::getListPointCloud()
{
    return this->listPointCloud;
}