#include <vector>

#include "CollisionManager.h"
#include "Particle.h"
#include "Vector3.h"


CollisionManager::CollisionManager()
{
	particles = std::vector<Particle>();
}

void CollisionManager::addParticle(Particle p)
{
	particles.push_back(p);
}

std::vector<Particle> CollisionManager::detectCollisions()
{
	int threshold = 2 * particles.size();
	int collisionNb = 0;
	
	for each (Particle p in particles)
	{
		for each (Particle q in particles)
		{
			if (p == q) continue;

			// Interpenetration
			if (Particle::distance(p, q) < p.getSize() + q.getSize())
			{
				// Cancel penetration
				Vector3 unit = q.getPosition() - p.getPosition();
				unit.normalise();
				p.setPosition(p.getPosition() + unit * (q.getMass() / (p.getMass() + q.getMass())));
				q.setPosition(q.getPosition() - unit * (p.getMass() / (p.getMass() + q.getMass())));
			}
		}
	}
	return particles; //tmp sinon erreur
}