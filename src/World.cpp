#include <vector>

#include "World.h"
#include "CollisionManager.h"

std::vector<Particle> World::Particles;

CollisionManager World::collisionManager = CollisionManager();

void World::addParticle(Particle p)
{
	Particles.push_back(p);
	collisionManager.addParticle(p);
}

Particle World::getParticle(int i) {
	if (i < World::Particles.size() && i >= 0)
	{
		return World::Particles[i];
	}
	return World::Particles[0];
}