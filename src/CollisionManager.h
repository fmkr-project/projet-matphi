#pragma once

#include <vector>

#include "Particle.h"

class CollisionManager
{
private:
	std::vector<Particle> particles;

public:
	CollisionManager();
	void addParticle(Particle p);
	std::vector<Particle> detectCollisions();
};