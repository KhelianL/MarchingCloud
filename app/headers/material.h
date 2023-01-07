#ifndef MATERIAL_H
#define MATERIAL_H

/* SRC */
#include <vec3.h>

enum class MaterialType
{
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
    Mirror
};

class Material
{
private:
    Vec3 ambiant, diffuse, specular;
    int spec_exp;
    float transparency, refractionIndex;

public:
    Material();
    Material(MaterialType type);

    // Getters
    Vec3 &getAmbiant();
    Vec3 &getDiffuse();
    Vec3 &getSpecular();
    int &getSpecExp();
    float &getTransparency();
    float &getRefractionIndex();

    // Setters
    void setAmbiant(Vec3 &ambiant);
    void setDiffuse(Vec3 &diffuse);
    void setSpecular(Vec3 &specular);
    void setSpecExp(int spec_exp);
    void setTransparency(float transparency);
    void setRefractionIndex(float refractionIndex);
};
#endif