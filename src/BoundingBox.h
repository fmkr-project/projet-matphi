#pragma once
#include "Vector3.h"
#include "RigidBody.h"

class BoundingBox
{

private:

	Vector3 min; //coin inférieur-gauche 
	Vector3 max; //coin supérieur-droit

public:
	
	BoundingBox();
	BoundingBox(Vector3 min, Vector3 max);
	BoundingBox(const BoundingBox& box);

	bool contains(const RigidBody& object);


	//Getters
	Vector3 getMin() { return min; }
	Vector3 getMax() { return max; }

	void draw();
};

