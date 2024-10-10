#pragma once
#include "Particle.h"

#ifndef PARTICLEFORCEGENERATOR_H
#define PARTICLEFORCEGENERATOR_H

class ParticleForceGenerator {

public:
	virtual void updateForce(Particle* particule, float duration) = 0;
};

#endif
