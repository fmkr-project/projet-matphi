#include "ParticleSpring.h"


ParticleSpring::ParticleSpring(float k, float l_init, Particle* anchor)
{
	this->k = k;
	this->l_init = l_init;
	anchorParticle = anchor;
}

void ParticleSpring::updateForce(Particle* particle, float duration) {
	Vector3 l = particle->getPosition() - anchorParticle->getPosition();
	Vector3 m = l;
	m.normalise();
	Vector3 springForce = k * (m * l_init - l);
	particle->addForce(springForce);
}