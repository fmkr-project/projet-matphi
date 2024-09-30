#ifndef WORLD_H
#define WORLD_H

#include <vector>

#include "Particle.h"

class World
{
	static std::vector<Particle> Particles;
	// std::vector<Collision> Collisions;

public:
	static void addParticle(Particle p);
};

#endif