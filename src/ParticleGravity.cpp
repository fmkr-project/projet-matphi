#include "ParticleForceGenerator.h"


class ParticleGravity : public ParticleForceGenerator {
	float gravity = 9.81;

	void UpdateForce(Particle* particle, float duration) {
		float m = 1 / particle->getInverseMass();
		if (m != 0) {
			particle->addForce(gravity * m);
		}
	}
};

