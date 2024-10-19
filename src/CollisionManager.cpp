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
		for each (Particle* q in particles)
		{
			if (p == q) continue;

			// Interpenetration
			if (Particle::distance(*p, *q) < p->getSize() + q->getSize())
			{
				collisionNb++;
				// Cancel penetration
				Vector3 unit = q->getPosition() - p->getPosition();
				unit.normalise();
				p->setPosition(p->getPosition() - unit * (q->getMass() / (p->getMass() + q->getMass())));
				q->setPosition(q->getPosition() + unit * (p->getMass() / (p->getMass() + q->getMass())));

				// Generate pulse
				// Consider a perfectly elastic collision (ie. e=1)
				float k = 2 * Vector3::dotProduct(q->getSpeed() - p->getSpeed(), unit) /
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
