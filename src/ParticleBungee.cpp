#include "ParticleBungee.h"

ParticleBungee::ParticleBungee(float k, float lInit, Particle* other)
{
    this->k = k;
    this->l_init = lInit;
    this->otherParticle = other;
}

void ParticleBungee::updateForce(Particle* particle, float duration) {
    Vector3 l = particle->getPosition() - otherParticle->getPosition();
    float length = l.magnitude();
    // if length smaller than init, no forces applied
    if (length <= l_init) return;

    Vector3 m = l;
    m.normalise();
    Vector3 springForce = -k * (length - l_init) * m;
    particle->addForce(springForce);
}