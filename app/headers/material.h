#ifndef MATERIAL_H
#define MATERIAL_H

/* QT */
#include <QString>

/* SRC */
#include <vec3.h>

enum class MaterialType
{
    Custom,
    Gold,
    Silver,
    Bronze,
    Copper,
    Wood,
    RedPlastic,
    GreenPlastic,
    BluePlastic,
    Ruby,
    Crystal,
    Water,
    Glass,
    WitchHair,
    Mirror,
    Donut,
    Fire
};
QString matToString(const MaterialType &type);

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
};
#endif