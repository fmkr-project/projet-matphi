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

	void UpdateForce(Particle* particle, float duration) {
		particle->addForce(k * (restPos - particle->getPosition()));
	}

};