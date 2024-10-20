#pragma once
#include "ParticleForceGenerator.h"

class ParticleSpring : public ParticleForceGenerator
{
private:
	float k;
	float l_init;

	Particle* anchorParticle;

public:

	ParticleSpring(float kInit, float l_init, Particle* anchor);

	void updateForce(Particle* particle, float duration);

};