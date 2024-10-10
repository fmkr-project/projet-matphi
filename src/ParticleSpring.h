#include "ParticleForceGenerator.h"

class ParticleSpring : public ParticleForceGenerator
{
private:
	float k;
	Vector3 restPos;

public:
	ParticleSpring(float k = 0, Vector3 pos = (0, 0, 0)) {
		k = k;
		restPos = pos;
	}

	void updateForce(Particle* particle, float duration) override {
		particle->addForce(k * (restPos - particle->getPosition()));
	}

};