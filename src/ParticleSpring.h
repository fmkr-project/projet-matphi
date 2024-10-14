#pragma once
#include "ParticleForceGenerator.h"

class ParticleSpring : public ParticleForceGenerator
{
private:
	float k;

	Vector3 restPos;

public:

	ParticleSpring(float kInit, Vector3 pos);

	void updateForce(Particle* particle, float duration);

};