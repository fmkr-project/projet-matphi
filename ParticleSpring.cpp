#include "ParticleSpring.h"

ParticleSpring::ParticleSpring(float k = 0, Vector3 pos = (0, 0, 0)) {
	k = k;
	restPos = pos;
}

void ParticleSpring::updateForce(Particle* particle, float duration) {
	Vector3 springForce = k * (restPos - particle->getPosition());
	particle->addForce(springForce);
}