#pragma once
#include <map>

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
	std::map<Particle*, bool> boundParticles;
	Register registrations;

public:

	ParticleForceRegistry() = default;
	ParticleForceRegistry(Particle* particle, ParticleForceGenerator* Fg);
	ParticleForceRegistry(const ParticleForceRegistry& other);
	~ParticleForceRegistry();

	// Actions on the registry
	void add(Particle* particle, ParticleForceGenerator* Fg);
	void remove(Particle* particle, ParticleForceGenerator* Fg);
	void clear();
	void updateForces(float duration);

	// Actions for binding particles
	void bind(Particle* particle);
	void unbind(Particle* particle);
	bool isBound(Particle* particle);
};

