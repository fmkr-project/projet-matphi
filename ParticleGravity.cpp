#include "ParticleGravity.h"
#include "consts.h"


ParticleGravity::ParticleGravity()
{
	gravity = g;
}

ParticleGravity::ParticleGravity(Vector3 gravity)
{
	gravity = gravity;
}

void ParticleGravity::updateForce(Particle* particle, float duration)
{
	float m = 1 / particle->getInverseMass();
	if (m != 0) {
		Vector3 gravityForce = m * gravity;
		particle->addForce(gravityForce);
	}
}
