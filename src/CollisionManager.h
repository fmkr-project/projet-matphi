#pragma once

#include <vector>

#include "Particle.h"
#include "RigidBodyBox.h"

class CollisionManager
{
private:
	std::vector<RigidBodyBox*> cubes;

public:
	CollisionManager();
	void add_cube(RigidBodyBox* r);
	void remove_cube(RigidBodyBox* r);
	std::vector<RigidBodyBox*> get_cubes();
	void clear_cubes();
	void detect_collisions();

	// debug
	void _debug_print_all_rigidbodies() const;
};
