#ifndef WORLD_H
#define WORLD_H

#include <vector>

#include "Particle.h"
#include "CollisionManager.h"

class World
{
	static std::vector<Particle> Particles;
	static CollisionManager collisionManager;

public:
	static void addParticle(Particle p);
};

#endif