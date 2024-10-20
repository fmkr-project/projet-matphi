#include "consts.h"
#include "Particle.h"
#include <of3dGraphics.h>


// Ctors
Particle::Particle() {
	position = Vector3();
	speed = Vector3(0, 0, 1);
	color = ofColor();
	mass = 1;
	size = 10.;
	accumForce = Vector3(0, 0, 0);
}

Particle::Particle(Vector3 pos, Vector3 spd, float m, float s)
{
	position = pos;
	previousPosition = pos;
	speed = spd;
	mass = m;
	size = s;
	accumForce = Vector3(0, 0, 0);
}

Particle::Particle(Vector3 pos, Vector3 spd, float m, float s, ofColor col)
{
	position = pos;
	previousPosition = pos;
	speed = spd;
	color = col;
	mass = m;
	size = s;
	accumForce = Vector3(0, 0, 0);
}

Particle::Particle(const Particle& other) {
	position = other.position;
	previousPosition = other.position;
	speed = other.speed;
	color = other.color;
	mass = other.mass;
	size = other.size;
	accumForce = other.accumForce;
}

// Dtor
Particle::~Particle() {

}

// Statics
float Particle::distance(const Particle& p, const Particle& q)
{
	return (p.position - q.position).norm();
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

float Particle::getMass()
{
	return this->mass;
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
{
	speed += accumForce * this->getInverseMass() * t;
	position += speed * t;
}

void Particle::verletIntegrate(float t)
{
	this->position = 2 * this->position - this->previousPosition + this->accumForce * pow(t, 2);
}

void Particle::move()
{
	previousPosition = position;
	this->eulerIntegrate(ofGetLastFrameTime());
	//this->verletIntegrate(ofGetLastFrameTime());
}

void Particle::draw() {
	ofDrawIcoSphere(position.v3(), 10);
}

void Particle::addForce(const Vector3& force) {
	accumForce += force;
}

void Particle::clearAccum() {
	accumForce = Vector3(0, 0, 0);
}

bool Particle::operator==(const Particle& p) const
{
	return
		(
			this->position == p.position &&
			this->size == p.size &&
			this->speed == p.speed
			);
}