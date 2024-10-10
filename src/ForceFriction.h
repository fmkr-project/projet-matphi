#pragma once
#include "ParticleForceGenerator.h"


class ForceFriction :
    public ParticleForceGenerator
{
private:
    //Valeurs dépendant des particules
    float k1;
    float k2;
public :
    //Initialise les valeurs pour les particules
    ForceFriction(float k1, float k2);
    virtual void updateForce(Particle* particle, float duration);
};

