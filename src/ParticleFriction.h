#pragma once
#include "ParticleForceGenerator.h"


class ParticleFriction :
    public ParticleForceGenerator
{
private:
    //Valeurs dpendant des particules
    float k1;
    float k2;
public:
    //Initialise les valeurs pour les particules
    ParticleFriction(float k1, float k2);
    virtual void updateForce(Particle* particle, float duration);
};

