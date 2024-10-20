#include "ParticleFriction.h"

ParticleFriction::ParticleFriction(float k1 = 0, float k2 = 0) {
	k1 = k1;
	k2 = k2;
}

void ParticleFriction::updateForce(Particle* particle, float duration) {
	Vector3 speed = Vector3(particle->getSpeed()); //Rcupration de la vitesse initiale de la particule
	//Application de la formule de cours
	float tmp = k1 * speed.norm() + k2 * pow(speed.norm(), 2);
	speed.normalise();
	Vector3 forceFriction = Vector3(-1 * speed * tmp);
	particle->addForce(forceFriction);
}