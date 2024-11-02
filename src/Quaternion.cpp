#include "Quaternion.h"

#include <valarray>

#include "Vector3.h"

Quaternion::Quaternion(float x, float y, float z, float w)
{
    this->x = x;
    this->y = y;
    this->z = z;
    this->w = w;
}

Quaternion::~Quaternion()
= default;

Quaternion Quaternion::operator-(const Quaternion& other) const
{
    return other * Conjugate(*this);
}

Quaternion Quaternion::operator*(const Quaternion &other) const
{
    Vector3 va = *new Vector3(this->x, this->y, this->z);
    Vector3 vb = *new Vector3(other.x, other.y, other.z);

    Vector3 vc = this->w * vb + other.w * va + Vector3::crossProduct(va, vb);
    return {
        this->w * other.w - Vector3::dotProduct(va, vb),
        vc.getX(),
        vc.getY(),
        vc.getZ()
    };
    /*
    return {
        this->w * other.w - this->x * other.x - this->y * other.y - this->z * other.z,  // 1
        this->w * other.x + this->x * other.w + this->y * other.z - this->z * other.y,  // i
        this->w * other.y - this->x * other.z + this->y * other.w + this->z * other.x,  // j
        this->w * other.z + this->x * other.y - this->y * other.x + this->z * other.w   // k
        };*/
}

Quaternion Quaternion::operator*(const float& other) const
{
    return {x * other, y * other, z * other, w * other};
}

Quaternion Quaternion::operator/(const float& other) const
{
    return {x / other, y / other, z / other, w / other};
}

Quaternion Quaternion::Neg(const Quaternion& a)
{
    return {-a.x, -a.y, -a.z, -a.w};
}

float Quaternion::Magnitude(const Quaternion& a)
{
    return static_cast<float>(std::pow(a.w * a.w + a.x * a.x + a.y * a.y + a.z * a.z, 0.5));
}

Quaternion Quaternion::Conjugate(const Quaternion& a)
{
    return {a.w, -a.x, -a.y, -a.z};
}

Quaternion Quaternion::Inverse(const Quaternion& a)
{
    return Conjugate(a) / Magnitude(a);
}

float Quaternion::Dot(const Quaternion& a, const Quaternion& b)
{
    return a.w * b.w + a.x * b.x + a.y * b.y + a.z * b.z;
}

Quaternion Quaternion::Power(const Quaternion& a, float pow)
{
    float alpha = acos(a.w);
    Vector3 va = *new Vector3(sin(pow * alpha) / alpha * *new Vector3(a.x, a.y, a.z));
    return {
        cos(pow * alpha),
        va.getX(),
        va.getY(),
        va.getZ()
    };
}

Quaternion Quaternion::Slerp(const Quaternion& a, const Quaternion& b, float t)
{
    return Power(b * Inverse(a), t) * a;
}