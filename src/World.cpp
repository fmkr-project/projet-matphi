#include <vector>

#include "World.h"

std::vector<Particle> World::Particles;

// std::vector<Collision> World::Collision

void World::addParticle(Particle p)
{
	Particles.push_back(p);
}
