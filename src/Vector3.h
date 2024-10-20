/**
* \file vector3.h
* Ce fichier contient la d?claration des m?thodes et des attributs de la classe Vector3
*/

#ifndef VECTOR3_H
#define VECTOR3_H

#include <iostream>
#include <ofEvents.h>

class Vector3
{
private:
    /**
     * @brief les 3 composantes du vecteur
    */
    float x_;
    float y_;
    float z_;

    /**
     * @brief 4e ?l?ment du vecteur qui va nous permettre d'homog?n?iser les attributs ci-dessus lors des projections
    */
    float w_;

public:
    // Constructors
    Vector3(float x = 0, float y = 0, float z = 0);
    Vector3(const Vector3& v);

    // Usual vectors
    static const Vector3* zero;
    // TODO add forward, up, right
    
    // Destructor
    ~Vector3();

    // Gettes and Setters
    float getX() const;
    float getY() const;
    float getZ() const;
    float getW() const;
    void setX(float x);
    void setY(float x);
    void setZ(float x);
    void setW(float x);

    // Methods
    Vector3& operator+=(const Vector3& v);
    Vector3& operator+=(float& d);
    Vector3& operator-=(const Vector3& v);
    Vector3& operator-=(float& d);
    Vector3& operator*=(const Vector3& v);
    Vector3& operator*=(float& d);
    Vector3& operator/=(float& d);
    void operator=(const Vector3& v);
    bool operator==(const Vector3& v) const;
    bool operator!=(const Vector3& v) const;

    float magnitude() const;
    void normalise();
    float dotProduct(const Vector3& v) const;
    static float dotProduct(const Vector3& v1, const Vector3& v2);
    Vector3 crossProduct(const Vector3& v) const;
    static Vector3 crossProduct(const Vector3& v1, const Vector3& v2);
    float norm() const;

    glm::vec2 v2() { return glm::vec2(x_, y_); };
    glm::vec3 v3() { return glm::vec3(x_, y_, z_); };
};

Vector3 operator+(const Vector3& v1, const Vector3& v2);
Vector3 operator-(const Vector3& v1, const Vector3& v2);
Vector3 operator*(const Vector3& v1, const Vector3& v2);
Vector3 operator*(const Vector3& v, float d);
Vector3 operator*(float d, const Vector3& v);
Vector3 operator/(const Vector3& v, float& d);

#endif
