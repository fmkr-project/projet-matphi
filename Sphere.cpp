#include "Sphere.h"

// Constructeurs
Sphere::Sphere() :
	center(Particle()), radius(1.f) {}

Sphere::Sphere(Particle p, float r) :
	center(p), radius(r) {}

Sphere::Sphere(Particle p) :
	center(p), radius(1.f) {}

Sphere::Sphere(float r) :
	center(Particle()), radius(r) {}

// getters 

Particle Sphere::getCenter() {
	return center;
}
float Sphere::getRadius() {
	return radius;
}

// setters
void Sphere::setCenter(Particle p) {
	center = p;
}
void Sphere::setRadius(float r) {
	radius = r;
}