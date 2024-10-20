#include "TwoParticlesSpring.h"

TwoParticlesSpring::TwoParticlesSpring(float k, float lInit, Particle* other)
{
    this->k = k;
    this->l_init = lInit;
    this->otherParticle = other;
}

void TwoParticlesSpring::updateForce(Particle* particle, float duration) {
    Vector3 l = particle->getPosition() - otherParticle->getPosition();
    Vector3 m = l;
    m.normalise();
    Vector3 springForce = -k * (l - l_init) * m;
    particle->addForce(springForce);
}