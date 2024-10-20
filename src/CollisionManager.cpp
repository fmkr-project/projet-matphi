#include <vector>

#include "CollisionManager.h"
#include "Particle.h"
#include "Vector3.h"


CollisionManager::CollisionManager()
{
	particles = std::vector<Particle*>();
}

void CollisionManager::add_particle(Particle* p)
{
	particles.push_back(p);
}

void CollisionManager::remove_particle(Particle* p)
{
	for (unsigned int i = 0; i < particles.size(); i++)
	{
		if (p == particles[i])
			particles.erase(particles.begin() + i);
	}
}


std::vector<Particle*> CollisionManager::get_particles()
{
	return particles;
}


void CollisionManager::detect_collisions()
{
	int threshold = 2 * particles.size();
	int collisionNb = 0;
	
	for each (Particle* p in particles)
	{
		if (collisionNb >= threshold) break;
		for each (Particle* q in particles)
		{
			if (collisionNb >= threshold) break;
			if (p == q) continue;

			// Interpenetration
			if (Particle::distance(*p, *q) < p->getSize() + q->getSize())
			{
				collisionNb++;
				// Cancel penetration
				Vector3 d = p->getSize() + q->getSize() - Particle::distance(*p, *q);
				Vector3 unit = q->getPosition() - p->getPosition();
				unit.normalise();
				p->setPosition(p->getPosition() - d * unit * (q->getMass() / (p->getMass() + q->getMass())));
				q->setPosition(q->getPosition() + d * unit * (p->getMass() / (p->getMass() + q->getMass())));

				// Generate pulse
				// Consider a near perfect elastic collision (ie. e=0.75)
				float k = 1.75 * Vector3::dotProduct(p->getSpeed() - q->getSpeed(), unit) /
					(p->getInverseMass() + q->getInverseMass());
				// Change particle speeds accordingly
				p->setSpeed(p->getSpeed() - k * p->getInverseMass() * unit);
				q->setSpeed(q->getSpeed() + k * q->getInverseMass() * unit);
			}
		}
	}
}


// debug
void CollisionManager::_debug_print_all_particles() const
{
	for (auto p : particles)
	{
		std::cout << p->getPosition().getX() << ' ' << p->getPosition().getY() << '\n';
	}
}
