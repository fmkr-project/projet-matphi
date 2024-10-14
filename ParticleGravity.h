#include "ParticleForceGenerator.h"
#include "Vector3.h"
#include "Particle.h"
#include "consts.h"


class ParticleGravity : public ParticleForceGenerator {
private:
	Vector3 gravity;

public:
	ParticleGravity();
	ParticleGravity(Vector3 gravity);

	void updateForce(Particle* particle, float duration);
};

