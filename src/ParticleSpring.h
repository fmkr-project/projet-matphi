#pragma once
#include "ParticleForceGenerator.h"

class ParticleSpring : public ParticleForceGenerator
{
private:
	float k;

	Particle* anchorParticle;

public:

	ParticleSpring(float kInit, Particle* anchor);

	void updateForce(Particle* particle, float duration);

};