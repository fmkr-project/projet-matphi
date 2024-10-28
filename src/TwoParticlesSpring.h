#pragma once

#include "ParticleForceGenerator.h"
class TwoParticlesSpring : public ParticleForceGenerator
{
private:
    float k; 
    float l_init; 
    Particle* otherParticle; 

public:
    TwoParticlesSpring(float kInit, float lInit, Particle* other);
    void updateForce(Particle* particle, float duration) override;
};
