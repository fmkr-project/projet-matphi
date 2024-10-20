#pragma once

#include "ParticleForceGenerator.h"
#include "Vector3.h"
#include "Particle.h"


class ParticleGravity : public ParticleForceGenerator {
private:
	Vector3 gravity;
public:
	ParticleGravity();
	ParticleGravity(Vector3 grav);

	void updateForce(Particle* particle, float duration);
};

