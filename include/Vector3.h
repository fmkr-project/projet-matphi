#ifndef VECTOR3
#define VECTOR3

class Vector3 {
  float x, y, z;
public:
  Vector3();
  Vector3(float, float, float);
  Vector3 operator + (const Vector3 v) const;
  Vector3 operator * (const float k) const;

  void print();
};

Vector3 operator * (const float k, const Vector3 v);

#endif
