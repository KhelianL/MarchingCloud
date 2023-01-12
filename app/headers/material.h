#ifndef MATERIAL_H
#define MATERIAL_H

/* QT */
#include <QString>

/* SRC */
#include <vec3.h>

enum class MaterialType
{
    CUSTOM,
    GOLD,
    SILVER,
    BRONZE,
    COPPER,
    WOOD,
    REDPLASTIC,
    GREENPLASTIC,
    BLUEPLASTIC,
    RUBY,
    CRYSTAL,
    WATER,
    GLASS,
    WITCHHAIR,
    DONUT,
    FIRE
};
constexpr static const char *MaterialTable[] = {
    "CUSTOM",
    "GOLD",
    "SILVER",
    "BRONZE",
    "COPPER",
    "WOOD",
    "REDPLASTIC",
    "GREENPLASTIC",
    "BLUEPLASTIC",
    "RUBY",
    "CRYSTAL",
    "WATER",
    "GLASS",
    "WITCHHAIR",
    "DONUT",
    "FIRE"};

std::string getMaterialTypeToString(const MaterialType &type);
MaterialType getStringToMaterialType(std::string s);

class Material
{
private:
    MaterialType type;
    Vec3 ambiant, diffuse, specular;
    int spec_exp;
    float transparency, refractionIndex;

public:
    Material();
    Material(const MaterialType &type);

    // Getters
    Vec3 &getAmbiant();
    Vec3 &getDiffuse();
    Vec3 &getSpecular();
    int &getSpecExp();
    float &getTransparency();
    float &getRefractionIndex();
    MaterialType &getType();

    // Setters
    void setAmbiant(const Vec3 &ambiant);
    void setDiffuse(const Vec3 &diffuse);
    void setSpecular(const Vec3 &specular);
    void setSpecExp(const int &spec_exp);
    void setTransparency(const float &transparency);
    void setRefractionIndex(const float &refractionIndex);
    void setType(const MaterialType &type);

    void setAmbiantR(const float &v);
    void setAmbiantG(const float &v);
    void setAmbiantB(const float &v);
    void setDiffuseR(const float &v);
    void setDiffuseG(const float &v);
    void setDiffuseB(const float &v);
    void setSpecularR(const float &v);
    void setSpecularG(const float &v);
    void setSpecularB(const float &v);
};
#endif