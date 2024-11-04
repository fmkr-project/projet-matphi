#pragma once
#include "Particle.h"
#include "Quaternion.h"
#include "Vector3.h"

class RigidBody
{
private:
	Particle center;
	Quaternion orientation;
	Vector3 angularVelocity;
public:
	RigidBody();
	RigidBody(Particle center, Quaternion orientation, Vector3 angularVelocity);
	RigidBody(const RigidBody& body);
	~RigidBody();
};

