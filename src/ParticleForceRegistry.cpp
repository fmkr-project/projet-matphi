#include "ParticleForceRegistry.h"
#include "Particle.h"
#include "ParticleForceGenerator.h"

ParticleForceRegistry::ParticleForceRegistry(Particle* particle, ParticleForceGenerator* fg) {
    registrations.push_back({ particle, fg });
}

ParticleForceRegistry::ParticleForceRegistry(const ParticleForceRegistry& other) {
    registrations = other.registrations;
}

ParticleForceRegistry::~ParticleForceRegistry()
{
}

void ParticleForceRegistry::add(Particle* particle, ParticleForceGenerator* Fg) {
    registrations.push_back({ particle, Fg });
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
}

void ParticleForceRegistry::clear() {
    registrations.clear();
}

void ParticleForceRegistry::updateForces(float duration) {
    for (auto it = registrations.begin(); it != registrations.end(); ++it) {
        it->Fg->updateForce(it->particle, duration);
    }
}


