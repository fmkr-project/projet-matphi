#include "Quaternion.h"

#include <valarray>

#include "Vector3.h"

Quaternion::Quaternion() {
    this->x = 0;
    this->y = 0;
    this->z = 0;
    this->w = 1;
}

Quaternion::Quaternion(float x, float y, float z, float w)
{
    this->x = x;
    this->y = y;
    this->z = z;
    this->w = w;
}

Quaternion::Quaternion(Vector3 v, float w)
{
    this->x = v.getX();
    this->y = v.getY();
    this->z = v.getZ();
    this->w = w;
}

Quaternion::~Quaternion()
= default;

Quaternion Quaternion::operator+(const Quaternion& other) const
{
    return {this->x + other.x, this->y + other.y, this->z + other.z, this->w + other.w};
}


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
        vc.getX(),
        vc.getY(),
        vc.getZ(),
        this->w * other.w - Vector3::dotProduct(va, vb)
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

Quaternion Quaternion::Euler(float yaw, float pitch, float roll)
{
    return
    {
        static_cast<float>(cos(0.5 * roll) * cos(0.5 * pitch) * cos(0.5 * yaw) + sin(0.5 * roll) * sin(0.5 * pitch) *
            sin(0.5 * yaw)),
        static_cast<float>(sin(0.5 * roll) * cos(0.5 * pitch) * cos(0.5 * yaw) - cos(0.5 * roll) * sin(0.5 * pitch) *
            sin(0.5 * yaw)),
        static_cast<float>(cos(0.5 * roll) * sin(0.5 * pitch) * cos(0.5 * yaw) + sin(0.5 * roll) * cos(0.5 * pitch) *
            sin(0.5 * yaw)),
        static_cast<float>(cos(0.5 * roll) * cos(0.5 * pitch) * sin(0.5 * pitch) - sin(0.5 * roll) * sin(0.5 * pitch) *
            cos(0.5 * yaw))
    };
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
        va,
        cos(pow * alpha)
    };
}

Quaternion Quaternion::Slerp(const Quaternion& a, const Quaternion& b, float t)
{
    return Power(b * Inverse(a), t) * a;
}

Matrix3 Quaternion::ToRotationMatrix(const Quaternion& a)
{
    return
    {
        static_cast<float>(2 * (pow(a.w, 2) + pow(a.x, 2)) - 1),
        static_cast<float>(2 * (a.x * a.y - a.w * a.z)),
        static_cast<float>(2 * (a.x * a.z + a.w * a.y)),
        static_cast<float>(2 * (a.x * a.y + a.w * a.z)),
        static_cast<float>(2 * (pow(a.w, 2) + pow(a.y, 2)) - 1),
        static_cast<float>(2 * (a.y * a.z - a.w * a.x)),
        static_cast<float>(2 * (a.x * a.z - a.w * a.y)),
        static_cast<float>(2 * (a.y * a.z + a.w * a.x)),
        static_cast<float>(2 * (pow(a.w, 2) + pow(a.z, 2)) - 1)
    };
}

Quaternion Quaternion::Normalize(const Quaternion& a)
{
    return a / Magnitude(a);
}



void Quaternion::toAxisAngle(Vector3& axis, float& angle) const {
    Quaternion q = *this;
    q = q / q.Magnitude(q);

    angle = 2 * acos(q.w) * 360 / 3.1415926535897932384;

    if (fabs(angle) < 1e-6) {
        axis.setX(1); 
        axis.setY(0);
        axis.setZ(0);
    }
    else {
        float s = sqrt(1 - q.w * q.w); 
        axis.setX(q.x / s);
        axis.setY(q.y / s);
        axis.setZ(q.z / s);
    }
}