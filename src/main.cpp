#include <iostream>

#include "Vector3.h"

int main() {
  Vector3 u(3,4,5);
  Vector3 v(2,6,6);
  Vector3 w = u+v;
  Vector3 x = (float) 42 * u;
  w.print();
  x.print();
  return 0;
}
