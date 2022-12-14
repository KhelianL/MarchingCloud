#include <material.h>

// Constructors
Material::Material()
{
    this->ambiant = Vec3(0.0f, 0.0f, 0.0f);
    this->diffuse = Vec3(0.5f, 0.5f, 0.5f);
    this->specular = Vec3(0.5f, 0.5f, 0.5f);
    this->spec_exp = 32;
    this->transparency = 0.0;
    this->refractionIndex = 1.0;
}
Material::Material(const MaterialType &type)
{
    this->type = type;
    switch (type)
    {
    case MaterialType::Gold:
        this->ambiant = Vec3(0.24725, 0.1995, 0.0745);
        this->diffuse = Vec3(0.75164, 0.60648, 0.22648);
        this->specular = Vec3(0.628281, 0.555802, 0.366065);
        this->spec_exp = 51.2;
        this->transparency = 0.0;
        this->refractionIndex = 0.0;
        break;
    case MaterialType::Silver:
        this->ambiant = Vec3(0.19225, 0.19225, 0.19225);
        this->diffuse = Vec3(0.50754, 0.50754, 0.50754);
        this->specular = Vec3(0.508273, 0.508273, 0.508273);
        this->spec_exp = 51.2;
        this->transparency = 0.0;
        this->refractionIndex = 0.0;
        break;
    case MaterialType::Bronze:
        this->ambiant = Vec3(0.2125, 0.1275, 0.054);
        this->diffuse = Vec3(0.714, 0.4284, 0.18144);
        this->specular = Vec3(0.393548, 0.271906, 0.166721);
        this->spec_exp = 25.6;
        this->transparency = 0.0;
        this->refractionIndex = 0.0;
        break;
    case MaterialType::Copper:
        this->ambiant = Vec3(0.19125, 0.0735, 0.0225);
        this->diffuse = Vec3(0.7038, 0.27048, 0.0828);
        this->specular = Vec3(0.256777, 0.137622, 0.086014);
        this->spec_exp = 12.8;
        this->transparency = 0.0;
        this->refractionIndex = 0.0;
        break;
    case MaterialType::Wood:
        this->ambiant = Vec3(0.3, 0.1, 0.1);
        this->diffuse = Vec3(0.6, 0.3, 0.3);
        this->specular = Vec3(0.1, 0.1, 0.1);
        this->spec_exp = 10.0;
        this->transparency = 0.0;
        this->refractionIndex = 0.0;
        break;
    case MaterialType::RedPlastic:
        this->ambiant = Vec3(0.3, 0.0, 0.0);
        this->diffuse = Vec3(0.6, 0.0, 0.0);
        this->specular = Vec3(0.8, 0.8, 0.8);
        this->spec_exp = 10.0;
        this->transparency = 0.0;
        this->refractionIndex = 0.0;
        break;
    case MaterialType::GreenPlastic:
        this->ambiant = Vec3(0.0, 0.3, 0.0);
        this->diffuse = Vec3(0.0, 0.6, 0.0);
        this->specular = Vec3(0.8, 0.8, 0.8);
        this->spec_exp = 10.0;
        this->transparency = 0.0;
        this->refractionIndex = 0.0;
        break;
    case MaterialType::BluePlastic:
        this->ambiant = Vec3(0.0, 0.0, 0.3);
        this->diffuse = Vec3(0.0, 0.0, 0.6);
        this->specular = Vec3(0.8, 0.8, 0.8);
        this->spec_exp = 10.0;
        this->transparency = 0.0;
        this->refractionIndex = 0.0;
        break;
    case MaterialType::Ruby:
        this->ambiant = Vec3(0.1745, 0.01175, 0.01175);
        this->diffuse = Vec3(0.61424, 0.04136, 0.04136);
        this->specular = Vec3(0.727811, 0.626959, 0.626959);
        this->spec_exp = 76.8;
        this->transparency = 0.0;
        this->refractionIndex = 0.0;
        break;
    case MaterialType::Crystal:
        this->ambiant = Vec3(0.1, 0.1, 0.1);
        this->diffuse = Vec3(0.4, 0.4, 0.4);
        this->specular = Vec3(0.9, 0.9, 0.9);
        this->spec_exp = 100.0;
        this->transparency = 0.9;
        this->refractionIndex = 1.5;
        break;
    case MaterialType::Water:
        this->ambiant = Vec3(0.0, 0.0, 0.2);
        this->diffuse = Vec3(0.0, 0.0, 0.6);
        this->specular = Vec3(0.9, 0.9, 0.9);
        this->spec_exp = 100.0;
        this->transparency = 0.9;
        this->refractionIndex = 1.33;
        break;
    case MaterialType::Glass:
        this->ambiant = Vec3(0.0, 0.0, 0.0);
        this->diffuse = Vec3(0.5, 0.5, 0.5);
        this->specular = Vec3(0.9, 0.9, 0.9);
        this->spec_exp = 100.0;
        this->transparency = 0.9;
        this->refractionIndex = 1.5;
        break;
    case MaterialType::Donut:
        this->ambiant = Vec3(0.8, 0.5, 0.2);
        this->diffuse = Vec3(0.9, 0.7, 0.3);
        this->specular = Vec3(0.1, 0.1, 0.1);
        this->spec_exp = 10.0;
        this->transparency = 0.0;
        this->refractionIndex = 0.0;
        break;
    case MaterialType::WitchHair:
        this->ambiant = Vec3(0.2, 0.2, 0.2);
        this->diffuse = Vec3(0.9, 0.9, 0.8);
        this->specular = Vec3(0.9, 0.9, 0.9);
        this->spec_exp = 10.0;
        this->transparency = 0.0;
        this->refractionIndex = 0.0;
        break;
    case MaterialType::Fire:
        this->ambiant = Vec3(0.5, 0.3, 0.1);
        this->diffuse = Vec3(1.0, 0.1, 0.05);
        this->specular = Vec3(0.9, 0.9, 0.9);
        this->spec_exp = 10.0;
        this->transparency = 0.0;
        this->refractionIndex = 0.0;
        break;
    default:
        this->type = MaterialType::Custom;
        this->ambiant = Vec3();
        this->diffuse = Vec3(0.5, 0.5, 0.5);
        this->specular = Vec3(0.5, 0.5, 0.5);
        this->spec_exp = 32;
        this->transparency = 0.0;
        this->refractionIndex = 1.0;
        break;
    }
}

// Getters
Vec3 &Material::getAmbiant() { return this->ambiant; }
Vec3 &Material::getDiffuse() { return this->diffuse; }
Vec3 &Material::getSpecular() { return this->specular; }
int &Material::getSpecExp() { return this->spec_exp; }
float &Material::getTransparency() { return this->transparency; }
float &Material::getRefractionIndex() { return this->refractionIndex; }
MaterialType &Material::getType() { return this->type; }

// Setters
void Material::setAmbiant(const Vec3 &ambiant) { this->ambiant = ambiant; }
void Material::setDiffuse(const Vec3 &diffuse) { this->diffuse = diffuse; }
void Material::setSpecular(const Vec3 &specular) { this->specular = specular; }
void Material::setSpecExp(const int &spec_exp) { this->spec_exp = spec_exp; }

void Material::setAmbiantR(const float &v) { this->ambiant.setX(v); }
void Material::setAmbiantG(const float &v) { this->ambiant.setY(v); }
void Material::setAmbiantB(const float &v) { this->ambiant.setZ(v); }
void Material::setDiffuseR(const float &v) { this->diffuse.setX(v); }
void Material::setDiffuseG(const float &v) { this->diffuse.setY(v); }
void Material::setDiffuseB(const float &v) { this->diffuse.setZ(v); }
void Material::setSpecularR(const float &v) { this->specular.setX(v); }
void Material::setSpecularG(const float &v) { this->specular.setY(v); }
void Material::setSpecularB(const float &v) { this->specular.setZ(v); }

void Material::setTransparency(const float &transparency) { this->transparency = transparency; }
void Material::setRefractionIndex(const float &refractionIndex) { this->refractionIndex = refractionIndex; }

// Enum to String
QString matToString(const MaterialType &type)
{
    QString res;
    switch (type)
    {
    case MaterialType::Custom:
        res = "Custom";
        break;
    case MaterialType::Gold:
        res = "Gold";
        break;
    case MaterialType::Silver:
        res = "Silver";
        break;
    case MaterialType::Bronze:
        res = "Bronze";
        break;
    case MaterialType::Copper:
        res = "Copper";
        break;
    case MaterialType::Wood:
        res = "Wood";
        break;
    case MaterialType::RedPlastic:
        res = "RedPlastic";
        break;
    case MaterialType::GreenPlastic:
        res = "GreenPlastic";
        break;
    case MaterialType::BluePlastic:
        res = "BluePlastic";
        break;
    case MaterialType::Ruby:
        res = "Ruby";
        break;
    case MaterialType::Crystal:
        res = "Crystal";
        break;
    case MaterialType::Water:
        res = "Water";
        break;
    case MaterialType::Glass:
        res = "Glass";
        break;
    case MaterialType::Mirror:
        res = "Mirror";
        break;
    default:
        res = "";
        break;
    }

    return res;
}
MaterialType stringToMat(const QString &type)
{

}