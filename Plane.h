#pragma once
#include "Vector3.h"

class Plane
{
private:

	Vector3 normal; //Normal du plan
	float distance; //Distance par rapport a l'origine

	Plane(const Vector3 n, float d) : normal(n), distance(d) {}

	Vector3 getNormal() { return normal; }
	float getDistance() { return distance; }
};

