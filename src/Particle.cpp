#include "consts.h"
#include "Particle.h"
#include <of3dGraphics.h>


Particle::Particle() {
	position = Vector3();
	speed = Vector3(0, 0, 1);
	color = ofColor();
	mass = 1;
	size = 100.;
	accumForce = Vector3(0, 0, 0);
}

Particle::Particle(Vector3 pos, Vector3 spd, float m, float s)
{
	position, previousPosition = pos;
	speed = spd;
	mass = m;
	size = s;
}

Particle::Particle(Vector3 pos, Vector3 spd, float m, float s, ofColor col)
{
	position, previousPosition = pos;
	speed = spd;
	color = col;
	mass = m;
	size = s;
	accumForce = Vector3(0, 0, 0);
}

Particle::Particle(const Particle& other) {
	position, previousPosition = other.position;
	speed = other.speed;
	color = other.color;
	mass = other.mass;
}

Particle::~Particle() {

}

Vector3 Particle::getPosition() {
	return position;
}

Vector3 Particle::getSpeed() {
	return speed;
}

ofColor Particle::getColor() {
	return color;
}

float Particle::getSize()
{
	return size;
}

float Particle::getInverseMass()
{
	return 1 / this->mass;
}

void Particle::setPosition(Vector3 pos) {
	position = pos;
}

void Particle::setSpeed(Vector3 vitesse) {
	speed = vitesse;
}

void Particle::setColor(ofColor col) {
	color = col;
}

void Particle::setSize(float s)
{
	size = s;
}

void Particle::eulerIntegrate(float t)
// Consider that the particle is only affected by its weight
{
	speed += t * g * mass;
	position += t * speed;
}

void Particle::verletIntegrate(float t)
{
	this->position = 2 * this->position - this->previousPosition + this->accumForce * pow(t, 2);
}

void Particle::move()
{
	previousPosition = position;
	this->eulerIntegrate(ofGetLastFrameTime());
}

void Particle::draw() {
	ofDrawIcoSphere(position.v3(), 5);
}

void Particle::addForce(const Vector3& force) {
	accumForce += force;
}

void Particle::clearAccum() {
	accumForce = Vector3(0, 0, 0);
}
