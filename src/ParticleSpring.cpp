#include "ParticleSpring.h"


ParticleSpring::ParticleSpring(float k, Particle* anchor)
{
	this->k = k;
	anchorParticle = anchor;
}

void ParticleSpring::updateForce(Particle* particle, float duration) {
	Vector3 springForce = k * (anchorParticle->getPosition() - particle->getPosition());
	particle->addForce(springForce);
}