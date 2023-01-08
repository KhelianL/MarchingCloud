#include <scene.h>

Scene::Scene()
{
    this->init();
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
}

void Scene::draw()
{
    int size = this->listPointCloud.size();
    for (int i = 0; i < size; i++)
        this->listPointCloud[i].draw();
}

void Scene::generateImport(const std::string &filename, const float &keepingPart)
{
    PointCloud res;
    res.loadPointCloud(filename);

    res.decimate(keepingPart);

    this->listPointCloud.push_back(res);
}

void Scene::generatePrimitive(const PopupType &type, const double &resolution)
{
    PointCloud res;
    switch (type)
    {
    case PopupType::PLANE:
        res.generatePlane(resolution);
        break;
    case PopupType::CUBE:
        res.generateCube(resolution);
        break;
    case PopupType::SPHERE:
        res.generateSphere(resolution);
        break;
    case PopupType::TORUS:
        res.generateTorus(resolution);
        break;
    default:
        break;
    }
    res.setMaterial(Material(MaterialType::Fire));
    this->listPointCloud.push_back(res);
}

std::vector<PointCloud> &Scene::getListPointCloud()
{
    return this->listPointCloud;
}