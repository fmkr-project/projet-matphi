#pragma once
#include "Particle.h"
#include "ParticleForceGenerator.h"

class ParticleForceRegistry
{
private:

	struct ParticleForceRegistration {
		Particle* particle;
		ParticleForceGenerator* Fg;
	};

	typedef std::vector<ParticleForceRegistration> Register;
	Register registrations;

public:

	ParticleForceRegistry() = default;
	ParticleForceRegistry(Particle* particle, ParticleForceGenerator* Fg);
	ParticleForceRegistry(const ParticleForceRegistry& other);
	~ParticleForceRegistry();

	void add(Particle* particle, ParticleForceGenerator* Fg);
	void remove(Particle* particle, ParticleForceGenerator* Fg);
	void clear();
	void updateForces(float duration);
};

