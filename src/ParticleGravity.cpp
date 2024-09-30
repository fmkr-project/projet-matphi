#include "ParticleForceGenerator.h"


class ParticleGravity : public ParticleForceGenerator {
	Vector3 gravity = Vector3();

	ParticleGravity() {
		gravity = Vector3(0, -9.81, 0);
	}

	void UpdateForce(Particle* particle, float duration) {
		float m = 1 / particle->getInverseMass();
		if (m != 0) {
			particle->addForce(gravity * m);
		}
	}
};

