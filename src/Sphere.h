#pragma once
#include "Particle.h"
#include "RigidBodyBox.h"

class Sphere
{
private:
	Particle center;
	float radius;

public:

	// Constructeurs
	Sphere();
	Sphere(Particle p, float r);
	Sphere(Particle p);
	Sphere(float r);

	// getters 

	Particle getCenter();
	float getRadius();

	// setters
	void setCenter(Particle p);
	void setRadius(float r);



};

