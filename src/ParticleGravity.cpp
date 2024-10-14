#pragma once

#include "ParticleGravity.h"
#include "consts.h"


ParticleGravity::ParticleGravity()
{
	gravity = g;
}

ParticleGravity::ParticleGravity(Vector3 grav)
{
	gravity = grav;
}

void ParticleGravity::updateForce(Particle* particle, float duration)
{
	float m = 1 / particle->getInverseMass();
	if (m != 0) {
		Vector3 gravityForce = m * gravity;
		particle->addForce(gravityForce);
	}
}
