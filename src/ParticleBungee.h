#pragma once
#include "ParticleForceGenerator.h"

class ParticleBungee : public ParticleForceGenerator
{
private:
    float k; 
    float l_init; 
    Particle* otherParticle; 

public:
    ParticleBungee(float kInit, float lInit, Particle* other);
    void updateForce(Particle* particle, float duration) override;
};
