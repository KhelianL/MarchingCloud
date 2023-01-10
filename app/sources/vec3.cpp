#include <vec3.h>

Vec3::Vec3()
{
    mVals[0] = 0.0;
    mVals[1] = 0.0;
    mVals[2] = 0.0;
}
Vec3::Vec3(float x, float y, float z)
{
    mVals[0] = x;
    mVals[1] = y;
    mVals[2] = z;
}

float Vec3::getX()
{
    return mVals[0];
}
float Vec3::getY()
{
    return mVals[1];
}
float Vec3::getZ()
{
    return mVals[2];
}

float Vec3::squareLength() const
{
    return mVals[0] * mVals[0] + mVals[1] * mVals[1] + mVals[2] * mVals[2];
}
float Vec3::length() const
{
    return sqrt(squareLength());
}
void Vec3::normalize()
{
    float L = length();
    mVals[0] /= L;
    mVals[1] /= L;
    mVals[2] /= L;
}

float Vec3::dot(Vec3 const &a, Vec3 const &b)
{
    return a[0] * b[0] + a[1] * b[1] + a[2] * b[2];
}
Vec3 Vec3::cross(Vec3 const &a, Vec3 const &b)
{
    return Vec3(a[1] * b[2] - a[2] * b[1],
                a[2] * b[0] - a[0] * b[2],
                a[0] * b[1] - a[1] * b[0]);
}
Vec3 Vec3::project(Vec3 const &point, Vec3 const &normalePlan, Vec3 const &pointPlan)
{
    return (point - Vec3::dot(point - pointPlan, normalePlan) * normalePlan);
}

float &Vec3::operator[](unsigned int c)
{
    return mVals[c];
}
float Vec3::operator[](unsigned int c) const
{
    return mVals[c];
}
void Vec3::operator=(Vec3 const &other)
{
    mVals[0] = other[0];
    mVals[1] = other[1];
    mVals[2] = other[2];
}
void Vec3::operator+=(Vec3 const &other)
{
    mVals[0] += other[0];
    mVals[1] += other[1];
    mVals[2] += other[2];
}
void Vec3::operator-=(Vec3 const &other)
{
    mVals[0] -= other[0];
    mVals[1] -= other[1];
    mVals[2] -= other[2];
}
void Vec3::operator*=(float s)
{
    mVals[0] *= s;
    mVals[1] *= s;
    mVals[2] *= s;
}
void Vec3::operator/=(float s)
{
    mVals[0] /= s;
    mVals[1] /= s;
    mVals[2] /= s;
}

Vec3 operator+(Vec3 const &a, Vec3 const &b)
{
    return Vec3(a[0] + b[0], a[1] + b[1], a[2] + b[2]);
}
Vec3 operator-(Vec3 const &a, Vec3 const &b)
{
    return Vec3(a[0] - b[0], a[1] - b[1], a[2] - b[2]);
}
Vec3 operator*(float a, Vec3 const &b)
{
    return Vec3(a * b[0], a * b[1], a * b[2]);
}
Vec3 operator*(Vec3 const &a, float b)
{
    return Vec3(b * a[0], b * a[1], b * a[2]);
}
Vec3 operator*(Vec3 const &a, Vec3 const &b)
{
    return Vec3(a[0] * b[0], a[1] * b[1], a[2] * b[2]);
}
Vec3 operator/(Vec3 const &a, float b)
{
    return Vec3(a[0] / b, a[1] / b, a[2] / b);
}

std::istream &operator>>(std::istream &in, Vec3 &v)
{
    in >> v.mVals[0] >> v.mVals[1] >> v.mVals[2];
    return in;
}
std::ostream &operator<<(std::ostream &out, Vec3 const &v)
{
    out << v.mVals[0] << " " << v.mVals[1] << " " << v.mVals[2];
    return out;
}
