#include "ParticleSpring.h"


ParticleSpring::ParticleSpring(float k)
{
	this->k = k;
	restPos = *Vector3::zero;
}

ParticleSpring::ParticleSpring(float k, Vector3 pos)
{
	this->k = k;
	restPos = pos;
}

void ParticleSpring::updateForce(Particle* particle, float duration) {
	Vector3 springForce = k * (restPos - particle->getPosition());
	particle->addForce(springForce);
}