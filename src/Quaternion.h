#pragma once
#include "Vector3.h"

class Quaternion
{
private:
    float x, y, z, w;

public:
    Quaternion();
    Quaternion(float x, float y, float z, float w);
    Quaternion(Vector3 v, float w);
    ~Quaternion();

    Quaternion static identity;

    Quaternion operator+(const Quaternion &other) const;
    Quaternion operator-(const Quaternion &other) const;
    Quaternion operator*(const Quaternion &other) const;

    Quaternion operator*(const float &other) const;
    Quaternion operator/(const float &other) const;

    Quaternion static Neg(const Quaternion &a);
    Quaternion static Euler(float yaw, float pitch, float roll);
    float static Magnitude(const Quaternion &a);
    Quaternion static Conjugate(const Quaternion &a);
    Quaternion static Inverse(const Quaternion &a);
    float static Dot(const Quaternion &a, const Quaternion &b);
    Quaternion static Power(const Quaternion &a, float pow);
    Quaternion static Slerp(const Quaternion &a, const Quaternion &b, float t);
};

