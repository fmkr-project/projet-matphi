#include <iostream>

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

Vector3 Vector3::operator * (const float k) const {
  return Vector3(k * this->x, k * this->y, k * this->z);
}

// Second operator to allow k*v style multiplications
Vector3 operator * (const float k, Vector3 v) {
  return v*k;
}

void Vector3::print() {
  printf("(%f, %f, %f)\n", x, y, z);
}
