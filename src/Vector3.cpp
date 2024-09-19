#include <iostream>
#include <cmath>

#include "Vector3.h"

Vector3::Vector3() {
  x=y=z = 0.;
}

Vector3::Vector3(float x, float y, float z) {
  this->x = x;
  this->y = y;
  this->z = z;
}

Vector3 Vector3::operator + (const Vector3 v) const {
  return Vector3(this->x + v.x, this->y + v.y, this->z + v.z);
}

Vector3 Vector3::operator - (const Vector3 v) const {
  return *this + (v * -1);
}

Vector3 Vector3::operator * (const float k) const {
  return Vector3(k * this->x, k * this->y, k * this->z);
}

// Second operator to allow k*v style multiplications
Vector3 operator * (const float k, Vector3 v) {
  return v*k;
}

// Static standard vectors
Vector3 Vector3::zero = Vector3(0, 0, 0);

// Static "operators"
// Multiply two vectors component-wise
Vector3 Vector3::scale(const Vector3 a, const Vector3 b) {
  return Vector3(a.x * b.x, a.y * b.y, a.z * b.z);
}

// Dot product
float Vector3::dot(const Vector3 a, const Vector3 b) {
  return a.x * b.x + a.y * b.y + a.z * b.z;
}

// Cross product
Vector3 Vector3::cross(const Vector3 a, const Vector3 b) {
  return Vector3(a.y * b.z - a.z * b.y,
                 a.z * b.x - a.x * b.z,
                 a.x * b.y - a.y * b.x);
}

float Vector3::magnitude() const {
  // We don't use sqrMagnitude for the sake of efficiency
  return pow(pow(this->x, 2) + pow(this->y, 2) + pow(this->z, 2), 0.5);
}

float Vector3::sqrMagnitude() const {
  return pow(this->x, 2) + pow(this->y, 2) + pow(this->z, 2);
}

Vector3 Vector3::normalized() const {
    float mag = this->magnitude();
    if (mag == 0) return Vector3(0, 0, 0); //handle division by 0
    return Vector3(this->x / mag, this->y / mag, this->z / mag);
}


void Vector3::print() {
  printf("(%f, %f, %f)\n", x, y, z);
}
