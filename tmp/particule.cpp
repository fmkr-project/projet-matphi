#include "particule.h"
#include <of3dGraphics.h>
#include "consts.h"

Particule::Particule() {
	position = Vector3d();
	speed = Vector3d();
	mass = 1;
	color = ofColor();
}

Particule::Particule(Vector3d pos, Vector3d spd, float m) {
	position = pos;
	speed = spd;
	mass = m;
}

Particule::Particule(Vector3d pos, Vector3d spd, float m, ofColor col) {
	position = pos;
	speed = spd;
	color = col;
	mass = m;
}

Particule::Particule(const Particule& other) {
	position = other.position;
	mass = other.mass;
	speed = other.speed;
	color = other.color;
}

Particule::~Particule() {

}

Vector3d Particule::getPosition() {
	return position;
}


Vector3d Particule::getSpeed() {
	return speed;
}

ofColor Particule::getColor() {
	return color;
}

float Particule::getInverseMass() {
	return 1 / this->mass;
}

void Particule::setPosition(Vector3d pos) {
	position = pos;
}

void Particule::setSpeed(Vector3d vitesse) {
	speed = vitesse;
}

void Particule::setColor(ofColor col) {
	color = col;
}

void Particule::eulerIntegrate(float t)
// Consider that the particle is only affected by its weight
{
	speed += t * g * mass;
	position += t * speed;
}

void Particule::move() {
	this->eulerIntegrate(ofGetLastFrameTime());
}

void Particule::draw() {
	ofDrawIcoSphere(position.v3(), 1);
}
