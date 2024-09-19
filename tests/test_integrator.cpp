#include <iostream>

#include "Particle.h"

void testEuler()
{
	Particle p(
		pos = Vector3.zero,
		dir = Vector3(1, 1, 0),
		spd = Vector3(5, 5, 0),
		m = 1
	);

	for (int i = 0; i < 10; i++)
	{
		p.eulerIntegrate(0.2f);
		p.getPosition.print();
	}
}