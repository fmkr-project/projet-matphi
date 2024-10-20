#include "ParticleForceRegistry.h"
#include "Particle.h"
#include "ParticleForceGenerator.h"
#include "ParticleGravity.h"

ParticleForceRegistry::ParticleForceRegistry(Particle* particle, ParticleForceGenerator* fg) {
    registrations.push_back({ particle, fg });;
    boundParticles.insert_or_assign(particle, true);
}

ParticleForceRegistry::ParticleForceRegistry(const ParticleForceRegistry& other) {
    registrations = other.registrations;
    boundParticles = other.boundParticles;
}

ParticleForceRegistry::~ParticleForceRegistry()
{
}

void ParticleForceRegistry::add(Particle* particle, ParticleForceGenerator* Fg) {
    registrations.push_back({ particle, Fg });
    boundParticles.insert_or_assign(particle, true);
}

void ParticleForceRegistry::remove(Particle* particle, ParticleForceGenerator* Fg)
{
    for (auto it = registrations.begin(); it != registrations.end(); ++it)
    {
        if (it->particle == particle && it->Fg == Fg)
        {
            registrations.erase(it);
            return;
        }
    }
    boundParticles.erase(particle);
}

void ParticleForceRegistry::bind(Particle* particle)
{
    boundParticles.insert_or_assign(particle, true);
}

void ParticleForceRegistry::unbind(Particle* particle)
{
    boundParticles.insert_or_assign(particle, false);
}

bool ParticleForceRegistry::isBound(Particle* particle)
{
    return boundParticles.at(particle);
}


void ParticleForceRegistry::clear() {
    registrations.clear();
}

void ParticleForceRegistry::updateForces(float duration) {
    // Clear accumulators first
    // TODO this is not very efficient
    for (auto it = registrations.begin(); it != registrations.end(); ++it)
    {
        it->particle->clearAccum();        
    }

    // Then, update forces applied to every particle
    for (auto it = registrations.begin(); it != registrations.end(); ++it)
    {
        // Apply all forces for bound particles
        if (boundParticles.at(it->particle))
        {
            it->Fg->updateForce(it->particle, duration);
            continue;
        }
    }
}


