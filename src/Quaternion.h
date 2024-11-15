#pragma once
#include "Vector3.h"  // Vérifiez que ce fichier existe et que Vector3 est bien défini

class Quaternion
{
private:

public:
    float x, y, z, w;

    // Constructeurs
    Quaternion();
    Quaternion(float x, float y, float z, float w);
    Quaternion(Vector3 v, float w);
    ~Quaternion();

    // Méthodes statiques
    static Quaternion identity;
    static Quaternion Neg(const Quaternion& a);
    static Quaternion Euler(float yaw, float pitch, float roll);
    static float Magnitude(const Quaternion& a);
    static Quaternion Conjugate(const Quaternion& a);
    static Quaternion Inverse(const Quaternion& a);
    static float Dot(const Quaternion& a, const Quaternion& b);
    static Quaternion Power(const Quaternion& a, float pow);
    static Quaternion Slerp(const Quaternion& a, const Quaternion& b, float t);

    // Opérateurs
    Quaternion operator+(const Quaternion& other) const;
    Quaternion operator-(const Quaternion& other) const;
    Quaternion operator*(const Quaternion& other) const;
    Quaternion operator*(const float& other) const;
    Quaternion operator/(const float& other) const;

    // Méthodes non statiques
    void toAxisAngle(Vector3& axis, float& angle) const;  
};
