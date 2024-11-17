#include "Quaternion.h"
#include <cmath>
#include "Vector3.h"

Quaternion::Quaternion() {
    this->w = 1; 
    this->x = 0;
    this->y = 0;
    this->z = 0;
}

Quaternion::Quaternion(float w, float x, float y, float z) {
    this->w = w; 
    this->x = x;
    this->y = y;
    this->z = z;
}

Quaternion::Quaternion(Vector3 v, float w) {
    this->w = w; 
    this->x = v.getX();
    this->y = v.getY();
    this->z = v.getZ();
}

Quaternion::~Quaternion() = default;

Quaternion Quaternion::operator+(const Quaternion& other) const {
    return { this->w + other.w, this->x + other.x, this->y + other.y, this->z + other.z };
}

Quaternion Quaternion::operator-(const Quaternion& other) const {
    return { this->w - other.w, this->x - other.x, this->y - other.y, this->z - other.z };
}

Quaternion Quaternion::operator*(const Quaternion& other) const {
    Vector3 va(this->x, this->y, this->z);
    Vector3 vb(other.x, other.y, other.z);

    Vector3 vc = this->w * vb + other.w * va + Vector3::crossProduct(va, vb);

    return {
        this->w * other.w - Vector3::dotProduct(va, vb),
        vc.getX(),
        vc.getY(),
        vc.getZ()
    };
}

Quaternion Quaternion::operator*(const float& other) const {
    return { w * other, x * other, y * other, z * other };
}

Quaternion Quaternion::operator/(const float& other) const {
    if (other == 0.0f) {
        throw std::runtime_error("Division by zero.");
    }
    return { w / other, x / other, y / other, z / other };
}

Quaternion Quaternion::Neg(const Quaternion& a) {
    return { -a.w, -a.x, -a.y, -a.z };
}

Quaternion Quaternion::Euler(float yaw, float pitch, float roll) {
    return {
        static_cast<float>(cos(0.5 * roll) * cos(0.5 * pitch) * cos(0.5 * yaw) + sin(0.5 * roll) * sin(0.5 * pitch) * sin(0.5 * yaw)),
        static_cast<float>(sin(0.5 * roll) * cos(0.5 * pitch) * cos(0.5 * yaw) - cos(0.5 * roll) * sin(0.5 * pitch) * sin(0.5 * yaw)),
        static_cast<float>(cos(0.5 * roll) * sin(0.5 * pitch) * cos(0.5 * yaw) + sin(0.5 * roll) * cos(0.5 * pitch) * sin(0.5 * yaw)),
        static_cast<float>(cos(0.5 * roll) * cos(0.5 * pitch) * sin(0.5 * yaw) - sin(0.5 * roll) * sin(0.5 * pitch) * cos(0.5 * yaw))
    };
}

float Quaternion::Magnitude(const Quaternion& a) {
    return std::sqrt(a.w * a.w + a.x * a.x + a.y * a.y + a.z * a.z);
}

Quaternion Quaternion::Conjugate(const Quaternion& a) {
    return { a.w, -a.x, -a.y, -a.z };
}

Quaternion Quaternion::Inverse(const Quaternion& a) {
    float magnitudeSquared = Magnitude(a) * Magnitude(a);
    if (magnitudeSquared == 0.0f) {
        throw std::runtime_error("Quaternion inverse undefined for zero magnitude.");
    }
    return a.Conjugate(a) / magnitudeSquared;
}

float Quaternion::Dot(const Quaternion& a, const Quaternion& b) {
    return a.w * b.w + a.x * b.x + a.y * b.y + a.z * b.z;
}

Quaternion Quaternion::Power(const Quaternion& a, float pow) {
    float alpha = acos(a.w);
    float s = sin(pow * alpha) / sin(alpha);
    return {
        cos(pow * alpha),
        s * a.x,
        s * a.y,
        s * a.z
    };
}

Quaternion Quaternion::Slerp(const Quaternion& a, const Quaternion& b, float t) {
    return Power(b * Inverse(a), t) * a;
}

Matrix3 Quaternion::ToRotationMatrix(const Quaternion& a) {
    return {
        static_cast<float>(2 * (a.w * a.w + a.x * a.x) - 1),
        static_cast<float>(2 * (a.x * a.y - a.w * a.z)),
        static_cast<float>(2 * (a.x * a.z + a.w * a.y)),

        static_cast<float>(2 * (a.x * a.y + a.w * a.z)),
        static_cast<float>(2 * (a.w * a.w + a.y * a.y) - 1),
        static_cast<float>(2 * (a.y * a.z - a.w * a.x)),

        static_cast<float>(2 * (a.x * a.z - a.w * a.y)),
        static_cast<float>(2 * (a.y * a.z + a.w * a.x)),
        static_cast<float>(2 * (a.w * a.w + a.z * a.z) - 1)
    };
}

Quaternion Quaternion::Normalize(const Quaternion& a) {
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
