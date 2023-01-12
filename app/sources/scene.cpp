#include <scene.h>

void Scene::draw(bool drawNormals)
{
    int size = this->listPointCloud.size();
    for (int i = 0; i < size; i++)
        this->listPointCloud[i].draw(drawNormals);
}

void Scene::generateImport(const std::string &filename, const float &keepingPart)
{
    PointCloud res;
    res.loadPointCloud(filename);

    res.decimate(keepingPart);

    this->listPointCloud.push_back(res);
}
void Scene::generatePrimitive(const PointCloudType &type, const int &resolution)
{
    if (resolution > 0)
    {
        PointCloud res;
        switch (type)
        {
        case PointCloudType::PLANE:
            res.generatePlane(resolution);
            break;
        case PointCloudType::CUBE:
            res.generateCube(resolution);
            break;
        case PointCloudType::SPHERE:
            res.generateSphere(resolution);
            break;
        case PointCloudType::TORUS:
            res.generateTorus(resolution);
            break;
        default:
            break;
        }
        res.setMaterial(Material(MaterialType::CUSTOM));
        this->listPointCloud.push_back(res);
    }
}

std::vector<PointCloud> &Scene::getListPointCloud()
{
    return this->listPointCloud;
}

PointCloud &Scene::getPointCloudAtIndex(const int &index)
{
    return this->listPointCloud[index];
}
void Scene::removePointCloudAtIndex(const int &index)
{
    this->listPointCloud.erase(this->listPointCloud.begin() + index);
}
void Scene::addPointCloud(const PointCloud &p)
{
    this->listPointCloud.push_back(p);
}