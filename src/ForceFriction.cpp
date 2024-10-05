#include "ForceFriction.h"

ForceFriction::ForceFriction(float k1 = 0, float k2 = 0) {
	k1 = k1;
	k2 = k2;
}

void ForceFriction::updateForce(Particle* particle, float duration) {
	Vector3 speed = Vector3(particle->getSpeed());
	float tmp = k1 * speed.norm() + k2 * pow(speed.norm(), 2);
	speed.normalise();
	Vector3 forceFriction = Vector3(-1 * speed * tmp);
	particle->addForce(forceFriction);
}