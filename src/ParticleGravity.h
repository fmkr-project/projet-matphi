#include "ParticleForceGenerator.h"
#include "consts.h"


class ParticleGravity : public ParticleForceGenerator {
private:
	Vector3 gravity;

public:

	ParticleGravity(Vector3 gravite = g) {
		gravity = gravite;
	}

	void updateForce(Particle* particle, float duration) override {
		float m = 1 / particle->getInverseMass();
		if (m != 0) {
			particle->addForce(m * gravity);
		}
	}
};

