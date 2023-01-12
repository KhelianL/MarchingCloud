#include <scene.h>
#include<sstream>

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

void Scene::generatePrimitive(const PopupType &type, const int &resolution)
{
    if (resolution > 0)
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
        res.setMaterial(Material(MaterialType::Custom));
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

std::string myToStringFloat(float a){
    std::stringstream ss;
    ss << a;
    return ss.str();
}


// TODO : add .json at the end?
// TODO : AJOUTER LE DISPLAY NORMAL EN OPTION ET PAS EN CAST SELECTED
// TODO : Override shortcut S (sterovision)
void Scene::sceneParserJSON(const std::string &filename)
{
    // String for popback "," if needed.
    std::string fileContent = "";
    fileContent += "[\n";
    /** START **/

    // Pour chaque PointCloud
    for (PointCloud &pointCloud : this->listPointCloud)
    {
        fileContent += "\t{\n";
        /** START POINTCLOUD **/

        // Type and Resolution
        PointCloudType &typePointCloud = pointCloud.getPointCloudType();
        int &resolution = pointCloud.getResolution();
        fileContent += "\t\t\"typePointCloud\":\"" + getPointCloudTypeToString(typePointCloud) + "\",\n";
        fileContent += "\t\t\"resolution\":" + myToStringFloat(resolution) + ",\n";

        // If IMPORT : save each positions/normals
        if (typePointCloud == PointCloudType::IMPORT)
        {
            // For Each positions
            std::string savePos;
            fileContent += "\t\t\"positions\":[\n";
            for (const Vec3 &position : pointCloud.getPositions())
            {
                fileContent += "\t\t\t[" + myToStringFloat(position[0]) + "," + myToStringFloat(position[1]) + "," + myToStringFloat(position[2]) + "],\n";
            }
            if (pointCloud.getPositions().size() > 1)
            {
                fileContent.pop_back();
                fileContent.pop_back();
                fileContent += "\n";
            }
            fileContent += "\t\t],\n";

            // For Each normals
            fileContent += "\t\t\"normals\":[\n";
            for (const Vec3 &normal : pointCloud.getNormals())
            {
                fileContent += "\t\t\t[" + myToStringFloat(normal[0]) + "," + myToStringFloat(normal[1]) + "," + myToStringFloat(normal[2]) + "],\n";
            }
            if (pointCloud.getNormals().size() > 1)
            {
                fileContent.pop_back();
                fileContent.pop_back();
                fileContent += "\n";
            }
            fileContent += "\t\t],\n";
        }

        // Relative Transforms
        const Vec3 &relativePosition = pointCloud.getRelativePosition();
        const Vec3 &relativeRotation = pointCloud.getRelativeRotation();
        const Vec3 &relativeScale = pointCloud.getRelativeScale();

        fileContent += "\t\t\"relative_position\":[" + myToStringFloat(relativePosition[0]) + "," + myToStringFloat(relativePosition[1]) + "," + myToStringFloat(relativePosition[2]) + "],\n";
        fileContent += "\t\t\"relative_rotation\":[" + myToStringFloat(relativeRotation[0]) + "," + myToStringFloat(relativeRotation[1]) + "," + myToStringFloat(relativeRotation[2]) + "],\n";
        fileContent += "\t\t\"relative_scale\":[" + myToStringFloat(relativeScale[0]) + "," + myToStringFloat(relativeScale[1]) + "," + myToStringFloat(relativeScale[2]) + "],\n";

        // Material
        Material &mat = pointCloud.getMaterial();
        MaterialType &typeMaterial = mat.getType();

        if (typeMaterial == MaterialType::Custom)
        {
            const Vec3 &matAmb = mat.getAmbiant();
            const Vec3 &matDif = mat.getDiffuse();
            const Vec3 &matSpe = mat.getSpecular();
            const int &matSpecExp = mat.getSpecExp();
            const float &matTransparency = mat.getTransparency();
            const float &matRefractionIndex = mat.getRefractionIndex();
            fileContent += "\t\t\"typeMaterial\":\"" + getMaterialTypeToString(typeMaterial).toStdString() + "\",\n";
            fileContent += "\t\t\"material\":{\n";
            fileContent += "\t\t\t\"ambient\":[" + myToStringFloat(matAmb[0]) + "," + myToStringFloat(matAmb[1]) + "," + myToStringFloat(matAmb[2]) + "],\n";
            fileContent += "\t\t\t\"diffuse\":[" + myToStringFloat(matDif[0]) + "," + myToStringFloat(matDif[1]) + "," + myToStringFloat(matDif[2]) + "],\n";
            fileContent += "\t\t\t\"specular\":[" + myToStringFloat(matSpe[0]) + "," + myToStringFloat(matSpe[1]) + "," + myToStringFloat(matSpe[2]) + "],\n";
            fileContent += "\t\t\t\"specular_exponent\":" + myToStringFloat(matSpecExp) + ",\n";
            fileContent += "\t\t\t\"transparency\":" + myToStringFloat(matTransparency) + ",\n";
            fileContent += "\t\t\t\"refraction_index\":" + myToStringFloat(matRefractionIndex) + "\n";
            fileContent += "\t\t}\n";
        }
        else
        {
            fileContent += "\t\t\"typeMaterial\":\"" + getMaterialTypeToString(typeMaterial).toStdString() + "\"\n";
        }

        /** END POINTCLOUD **/
        fileContent += (this->listPointCloud.size() == 1 ? "\t}\n" : "\t},\n");
    }
    if (this->listPointCloud.size() > 1)
    {
        fileContent.pop_back();
        fileContent.pop_back();
        fileContent += "\n";
    }

    /** END **/
    fileContent += "]";

    std::ofstream jsonFile(filename);
    jsonFile << fileContent;
}