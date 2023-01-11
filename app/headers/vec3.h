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
    void setX(float const &v);
    void setY(float const &v);
    void setZ(float const &v);

    float squareLength() const;
    float length() const;
    void normalize();

    static float dot(Vec3 const &a, Vec3 const &b);
    static Vec3 cross(Vec3 const &a, Vec3 const &b);
    static Vec3 project(Vec3 const &point, Vec3 const &normalePlan, Vec3 const &pointPlan);

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

    static Vec3 multMat4(const float matrix[16], const Vec3 &vec);
    static Vec3 multMat4N(const float matrix[16], const Vec3 &vec);

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
std::ostream &operator<<(std::ostream &out, Vec3 const &v);

#endif