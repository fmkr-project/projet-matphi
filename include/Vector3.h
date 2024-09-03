#ifndef VECTOR3
#define VECTOR3

#include <functional>

class Vector3 {
public:
  float x, y, z;
  // Ctors
  Vector3();
  Vector3(float, float, float);
  
  // Standard vector addition
  Vector3 operator + (const Vector3 v) const;
  // Standard vector subtraction
  Vector3 operator - (const Vector3 v) const;
  // Standard vector scaling
  Vector3 operator * (const float k) const;

  // Static "operators"
  // Multiply two vectors component-wise
  static Vector3 scale(const Vector3 a, const Vector3 b);
  // Dot product
  static float dot(const Vector3 a, const Vector3 b);
  // Cross product
  static Vector3 cross(const Vector3 a, const Vector3 b);
  
  // Method names come from the Unity Vector3 class
  float magnitude() const; // TODO find a way to transform this into an attribute, like in Unity
  float sqrMagnitude() const;
  Vector3 normalized() const;

  void print();
};

Vector3 operator * (const float k, const Vector3 v);

#endif
