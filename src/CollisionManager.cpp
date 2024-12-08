#include <vector>

#include "CollisionManager.h"
#include "Particle.h"
#include "RigidBodyBox.h"
#include "Vector3.h"
#include "CollisionBoxPlane.h"


CollisionManager::CollisionManager()
{
	cubes = std::vector<RigidBodyBox*>();
}

void CollisionManager::add_cube(RigidBodyBox* r)
{
	cubes.push_back(r);
}

void CollisionManager::remove_cube(RigidBodyBox* r)
{
	for (unsigned int i = 0; i < cubes.size(); i++)
	{
		if (r == cubes[i])
			cubes.erase(cubes.begin() + i);
	}
}

void CollisionManager::clear_cubes()
{
	cubes.clear();
}



std::vector<RigidBodyBox*> CollisionManager::get_cubes()
{
	return cubes;
}


void CollisionManager::detect_collisions()
{
	int threshold = 2 * cubes.size();
	int collisionNb = 0;
	
	for each (RigidBodyBox* p in cubes)
	{
		if (collisionNb >= threshold) break;
		
		Particle& r = p->getCenterMass();
		for each (RigidBodyBox* q in cubes)
		{
			Particle& s = q->getCenterMass();
			
			if (collisionNb >= threshold) break;
			if (p == q) continue;

			CollisionBoxResult collisionResult = RigidBodyBox::testCollision(*p, *q);

			// Interpenetration
			if (collisionResult.hasCollision)
			{
				collisionNb++;
				// Cancel penetration
				Vector3 unit = collisionResult.collisionNormal;
				float d = collisionResult.penetrationDepth;
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