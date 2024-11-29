#include <vector>

#include "CollisionManager.h"
#include "Particle.h"
#include "Vector3.h"


CollisionManager::CollisionManager()
{
	rigidBodies = std::vector<RigidBody*>();
}

void CollisionManager::add_rigidbody(RigidBody* r)
{
	rigidBodies.push_back(r);
}

void CollisionManager::remove_rigidbody(RigidBody* r)
{
	for (unsigned int i = 0; i < rigidBodies.size(); i++)
	{
		if (r == rigidBodies[i])
			rigidBodies.erase(rigidBodies.begin() + i);
	}
}


std::vector<RigidBody*> CollisionManager::get_rigidbodies()
{
	return rigidBodies;
}


void CollisionManager::detect_collisions()
{
	int threshold = 2 * rigidBodies.size();
	int collisionNb = 0;

	
	for each (RigidBody* p in rigidBodies)
	{
		if (collisionNb >= threshold) break;
		
		Particle r = p->getCenterMass();
		for each (RigidBody* q in rigidBodies)
		{
			Particle s = q->getCenterMass();
			
			if (collisionNb >= threshold) break;
			if (r == s) continue;

			// Interpenetration
			if (Particle::distance(r, s) < r.getSize() + s.getSize())
			{
				collisionNb++;
				// Cancel penetration
				Vector3 d = r.getSize() + s.getSize() - Particle::distance(r, s);
				Vector3 unit = s.getPosition() - r.getPosition();
				unit.normalise();
				r.setPosition(r.getPosition() - d * unit * (s.getMass() / (r.getMass() + s.getMass())));
				s.setPosition(s.getPosition() + d * unit * (r.getMass() / (r.getMass() + s.getMass())));

				// Generate pulse
				// Consider a near perfect elastic collision (ie. e=0.75)
				float k = 1.75 * Vector3::dotProduct(r.getSpeed() - s.getSpeed(), unit) /
					(r.getInverseMass() + s.getInverseMass());
				// Change particle speeds accordingly
				r.setSpeed(r.getSpeed() - k * r.getInverseMass() * unit);
				s.setSpeed(s.getSpeed() + k * s.getInverseMass() * unit);
			}
		}
	}
}


// debug
/*
void CollisionManager::_debug_print_all_particles() const
{
	for (auto p : particles)
	{
		std::cout << r.getPosition().getX() << ' ' << r.getPosition().getY() << '\n';
	}
}
*/