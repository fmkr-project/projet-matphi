#include <of3dGraphics.h>

#include "Vector3.h"
#include "Particle.h"
#include "consts.h"

Particle::Particle() {
	position = Vector3();
	direction = Vector3();
	speed = Vector3;
	mass = 1;
}

Particle::Particle(Vector3 pos, Vector3 dir, Vector3 spd, float m) {
	position = pos;
	direction = dir;
	speed = spd;
	mass = m;
}

Particle::Particle(const Particle& other) {
	position = other.position;
	direction = other.direction;
	speed = other.speed;
	mass = other.mass;
}

Particle::~Particle() {

}

Vector3 Particle::getPosition() {
	return position;
}

Vector3 Particle::getDirection() {
	return direction;
}


Vector3 Particle::getSpeed() {
	return speed;
}

float Particle::getInverseMass()
{
	return 1/mass;
}
	
void Particle::setPosition(Vector3 pos) {
	position = pos;
}

void Particle::setDirection(Vector3 dir) {
	direction = dir;
}

void Particle::setSpeed(Vector3 vitesse) {
	speed = vitesse;
}

void Particle::move() {
	position += direction * speed;
}

void Particle::draw() {
	ofDrawIcoSphere(position.v3(), 10);
}

void Particle::eulerIntegrate(float t)
// Consider that the particle is only affected by its weight
{
	speed += t * g;
	position += t * speed;
}
