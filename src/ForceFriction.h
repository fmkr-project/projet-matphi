#pragma once
#include "ParticleForceGenerator.h"


class ForceFriction :
    public ParticleForceGenerator
{
private:
    float k1;
    float k2;
public :

    ForceFriction(float k1, float k2);

    virtual void updateForce(Particle* particle, float duration);
};

