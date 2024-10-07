#include "ParticleForceGenerator.h"
#include "consts.h"


class ParticleGravity : public ParticleForceGenerator {
private :
	Vector3 gravity;

public:

	ParticleGravity(Vector3 g = g) {
		gravity = g;
	}

	void UpdateForce(Particle* particle, float duration) {
		float m = 1 / particle->getInverseMass();
		if (m != 0) {
			particle->addForce(m * gravity);
		}
	}
};

