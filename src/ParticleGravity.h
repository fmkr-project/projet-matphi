#pragma once
#include "ParticleForceGenerator.h"

class ParticleGravity : public ParticleForceGenerator 
{
private :
	Vector3 gravity;

public :

	ParticleGravity(Vector3 gravite);

	void updateForce(Particle* particle, float duration);
};

