#ifndef VEC3_H
#define VEC3_H

/* C++ */
#include <cmath>    // sqrt, sqrtf
#include <iostream> // cout

class Vec3
{
private:
    float mVals[3];

public:
    Vec3();
    Vec3(float x, float y, float z);

    float getX();
    float getY();
    float getZ();

    float squareLength() const;
    float length() const;
    void normalize();

    static float dot(Vec3 const &a, Vec3 const &b);
    static Vec3 cross(Vec3 const &a, Vec3 const &b);
    static Vec3 project(Vec3 point, Vec3 normalePlan, Vec3 pointPlan);

    float &operator[](unsigned int c);
    float operator[](unsigned int c) const;
    void operator=(Vec3 const &other);
    void operator+=(Vec3 const &other);
    void operator-=(Vec3 const &other);
    void operator*=(float s);
    void operator/=(float s);

    friend Vec3 operator+(Vec3 const &a, Vec3 const &b);
    friend Vec3 operator-(Vec3 const &a, Vec3 const &b);
    friend Vec3 operator*(float a, Vec3 const &b);
    friend Vec3 operator*(Vec3 const &a, Vec3 const &b);
    friend Vec3 operator/(Vec3 const &a, float b);

    friend std::istream &operator>>(std::istream &in, Vec3 &v);
    friend std::ostream &operator<<(std::ostream &out, const Vec3 &v);
};

Vec3 operator+(Vec3 const &a, Vec3 const &b);
Vec3 operator-(Vec3 const &a, Vec3 const &b);
Vec3 operator*(float a, Vec3 const &b);
Vec3 operator*(Vec3 const &a, float b);
Vec3 operator*(Vec3 const &a, Vec3 const &b);
Vec3 operator/(Vec3 const &a, float b);

std::istream &operator>>(std::istream &in, Vec3 &v);
std::ostream &operator<<(std::ostream &out, const Vec3 &v);

#endif