/**
* \file vector3d.h
* Ce fichier contient la d?claration des m?thodes et des attributs de la classe Vector3d
*/

#ifndef VECTOR3D_H
#define VECTOR3D_H

#include <iostream>
#include <ofEvents.h>

class Vector3d
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
    Vector3d(float x = 0, float y = 0, float z = 0);
    Vector3d(const Vector3d& v);

    // Destructor
    ~Vector3d();

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
    Vector3d& operator+=(const Vector3d& v);
    Vector3d& operator+=(float& d);
    Vector3d& operator-=(const Vector3d& v);
    Vector3d& operator-=(float& d);
    Vector3d& operator*=(const Vector3d& v);
    Vector3d& operator*=(float& d);
    Vector3d& operator/=(float& d);
    void operator=(const Vector3d& v);
    bool operator==(const Vector3d& v) const;
    bool operator!=(const Vector3d& v) const;

    void normalise();
    float dotProduct(const Vector3d& v) const;
    Vector3d crossProduct(const Vector3d& v) const;

    glm::vec2 v2() { return glm::vec2(x_, y_); };
    glm::vec3 v3() { return glm::vec3(x_, y_, z_); };
};

Vector3d operator+(const Vector3d& v1, const Vector3d& v2);
Vector3d operator-(const Vector3d& v1, const Vector3d& v2);
Vector3d operator*(const Vector3d& v1, const Vector3d& v2);
Vector3d operator*(const Vector3d& v, float d);
Vector3d operator*(float d, const Vector3d& v);
Vector3d operator/(const Vector3d& v, float& d);



#endif

class vector3d
{
};


