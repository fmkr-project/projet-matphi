#pragma once

#include <vector>

#include "Particle.h"
#include "RigidBody.h"

class CollisionManager
{
private:
	std::vector<RigidBody*> rigidBodies;

public:
	CollisionManager();
	void add_rigidbody(RigidBody* r);
	void remove_rigidbody(RigidBody* r);
	std::vector<RigidBody*> get_rigidbodies();
	void detect_collisions();

	// debug
	void _debug_print_all_rigidbodies() const;
};
