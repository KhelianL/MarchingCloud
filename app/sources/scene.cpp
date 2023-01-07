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
    PointCloud dino3;
    dino3.loadPointCloud("dataPointsets/dino_subsampled_extreme.pn");
    dino3.move({2.0, 0.0, 0.0});
    dino3.setMaterial(Material(MaterialType::Gold));
    this->listPointCloud.push_back(dino3);
    */
    
    PointCloud testSphere;
    testSphere.generateSphere(50);
    this->listPointCloud.push_back(testSphere);

    PointCloud testPlane;
    testPlane.generatePlane(50);
    this->listPointCloud.push_back(testPlane);

    PointCloud testCube;
    testCube.generateCube(50);
    this->listPointCloud.push_back(testCube);

    PointCloud testTorus;
    testTorus.generateTorus(50);
    this->listPointCloud.push_back(testTorus);

    // PointCloud testRabbit;
    // testRabbit.generateRabbit(50);
    // this->listPointCloud.push_back(testRabbit);

    
}

void Scene::generateImport(const std::string &filename)
{
    PointCloud p;
    p.loadPointCloud(filename);
    this->listPointCloud.push_back(p);
}

std::vector<PointCloud> &Scene::getListPointCloud()
{
    return this->listPointCloud;
}