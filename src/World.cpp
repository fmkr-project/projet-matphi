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
