#pragma once

#include <vector>

#include "Particle.h"

class CollisionManager
{
private:
	std::vector<Particle> particles;

public:
	CollisionManager();
	void add_particle(Particle p);
	void remove_particle(Particle p);
	std::vector<Particle> get_particles();
	void detect_collisions();
};