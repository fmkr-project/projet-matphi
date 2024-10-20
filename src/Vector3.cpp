/**
* \file vector3d.cpp
* Ce fichier contient la d?finition des m?thodes de la classe Vector3
*/

#include "Vector3.h"
#include <cmath>

using namespace std;

/**
 * @brief Constructeur par d?faut et valu?
 *
 * @param x premier ?l?ment du vecteur
 * @param y deuxi?me ?l?ment du vecteur
 * @param z troisi?me ?l?ment du vecteur
 */
Vector3::Vector3(float x, float y, float z)
{
    x_ = x;
    y_ = y;
    z_ = z;

    w_ = 1.0f;
}

/**
 * @brief Constructeur de copie
 *
 * @param t le triangle ? copier
 */
Vector3::Vector3(const Vector3& v)
{
    x_ = v.x_;
    y_ = v.y_;
    z_ = v.z_;

    w_ = 1.0f;
}

/**
 * @brief Destructeur
 */
Vector3::~Vector3()
{

}



// ============================================================================
// Getters / Setters ==========================================================
// ============================================================================

float Vector3::getX() const
{
    return x_;
}

float Vector3::getY() const
{
    return y_;
}

float Vector3::getZ() const
{
    return z_;
}

float Vector3::getW() const
{
    return w_;
}

void Vector3::setX(float x)
{
    x_ = x;
}

void Vector3::setY(float y)
{
    y_ = y;
}

void Vector3::setZ(float z)
{
    z_ = z;
}

void Vector3::setW(float w)
{
    w_ = w;
}



// ============================================================================
// Surcharge d'op?rateurs =====================================================
// ============================================================================

Vector3& Vector3::operator+=(const Vector3& v)
{
    x_ += v.x_;
    y_ += v.y_;
    z_ += v.z_;

    return *this;
}

Vector3& Vector3::operator+=(float& d)
{
    x_ += d;
    y_ += d;
    z_ += d;

    return *this;
}

Vector3& Vector3::operator-=(const Vector3& v)
{
    x_ -= v.x_;
    y_ -= v.y_;
    z_ -= v.z_;

    return *this;
}

Vector3& Vector3::operator-=(float& d)
{
    x_ -= d;
    y_ -= d;
    z_ -= d;

    return *this;
}

Vector3& Vector3::operator*=(const Vector3& v)
{
    x_ *= v.x_;
    y_ *= v.y_;
    z_ *= v.z_;

    return *this;
}

Vector3& Vector3::operator*=(float& d)
{
    x_ *= d;
    y_ *= d;
    z_ *= d;

    return *this;
}

Vector3& Vector3::operator/=(float& f)
{
    if (f == 0)
    {
        throw std::invalid_argument("Division by zero");
    }

    x_ /= f;
    y_ /= f;
    z_ /= f;

    return *this;
}

void Vector3::operator=(const Vector3& v)
{
    if (this != &v)
    {
        x_ = v.x_;
        y_ = v.y_;
        z_ = v.z_;
    }
}

bool Vector3::operator==(const Vector3& v) const
{
    return (x_ == v.x_ && y_ == v.y_ && z_ == v.z_);
}


bool Vector3::operator!=(const Vector3& v) const
{
    return !(*this == v);
}



// ============================================================================
// ============================================================================
// ============================================================================

float Vector3::magnitude() const {
    return std::sqrt(x_ * x_ + y_ * y_ + z_ * z_); 
}

/**
 * @brief Normalise le vecteur courant
 *
 * @return rien
*/
void Vector3::normalise()
{
    float length = sqrt(x_ * x_ + y_ * y_ + z_ * z_);

    if (length != 0)
    {
        x_ /= length;
        y_ /= length;
        z_ /= length;
    }
}


/**
 * @brief Effectue le produit scalaire entre 2 vecteurs
 *
 * @param v le second vecteur
 * @return le produit scalaire entre le vecteur courant et le param?tre
*/
float Vector3::dotProduct(const Vector3& v) const
{
    return x_ * v.x_ + y_ * v.y_ + z_ * v.z_;
}

float Vector3::dotProduct(const Vector3& v1, const Vector3& v2)
{
    return v1.dotProduct(v2);
}


/**
 * @brief Effectue le produit vectoriel entre 2 vecteurs
 *
 * @param v l'autre vecteur pour le produit vectoriel
 * @return le produit vectoriel entre le vecteur courant et le param?tre
*/
Vector3 Vector3::crossProduct(const Vector3& v) const
{
    float x = y_ * v.z_ - z_ * v.y_;
    float y = z_ * v.x_ - x_ * v.z_;
    float z = x_ * v.y_ - y_ * v.x_;

    return Vector3(x, y, z);
}

Vector3 Vector3::crossProduct(const Vector3& v1, const Vector3& v2)
{
    return v1.crossProduct(v2);
}

float Vector3::norm() const {
    return sqrt(pow(x_, 2) + pow(y_, 2) + pow(z_, 2));
}



// ============================================================================
// Op?rateurs externes ========================================================
// ============================================================================

/**
 * @brief Additionne 2 vecteurs
 *
 * @param v1 le premier vecteur
 * @param v2 le deuxi?me vecteur, celui ? additionner
 * @return le vecteur r?sultat
*/
Vector3 operator+(const Vector3& v1, const Vector3& v2)
{
    Vector3 resu = Vector3(v1);
    return resu += v2;
}

/**
 * @brief soustraction de 2 vecteurs
 *
 * @param v1 le premier vecteur
 * @param v2 le deuxi?me vecteur, celui ? soustraire
 * @return le vecteur r?sultat
*/
Vector3 operator-(const Vector3& v1, const Vector3& v2)
{
    Vector3 resu = Vector3(v1);
    return resu -= v2;
}

/**
 * @brief Multiplie 2 vecteurs
 *
 * @param v1 le premier vecteur
 * @param v2 le deuxi?me vecteur, celui ? multiplier
 * @return le vecteur r?sultat
*/
Vector3 operator*(const Vector3& v1, const Vector3& v2)
{
    Vector3 resu = Vector3(v1);
    return resu *= v2;
}

/**
 * @brief Multiplie 21 vecteur et un scalaire
 *
 * @param v1 le premier vecteur
 * @param v2 le deuxi?me vecteur, celui ? multiplier
 * @return le vecteur r?sultat
*/
Vector3 operator*(const Vector3& v1, float f)
{
    Vector3 resu = Vector3(v1);
    return resu *= f;
}

/**
 * @brief Multiplie 21 vecteur et un scalaire
 *
 * @param v1 le premier vecteur
 * @param v2 le deuxi?me vecteur, celui ? multiplier
 * @return le vecteur r?sultat
*/
Vector3 operator*(float f, const Vector3& v1)
{
    Vector3 resu = Vector3(v1);
    return resu *= f;
}

/**
 * @brief Divise un vecteur par un flotant
 *
 * @param v le vecteur
 * @param f le flotant
 * @return le vecteur r?sultat
*/
Vector3 operator/(const Vector3& v, float& f)
{
    Vector3 resu = v;
    return resu /= f;
}


// Usual vectors
const Vector3* Vector3::zero = new Vector3(0, 0, 0);