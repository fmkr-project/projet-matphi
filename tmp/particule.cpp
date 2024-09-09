#include "particule.h"
#include <of3dGraphics.h>

Particule::Particule() {
	position = Vector3d();
	direction = Vector3d();
	speed = 0;
}

Particule::Particule(Vector3d pos, Vector3d dir, float spd) {
	position = pos;
	direction = dir;
	speed = spd ;
}

Particule::Particule(const Particule& other) {
	position = other.position;
	direction = other.direction;
	speed = other.speed;
}

Particule::~Particule() {

}

Vector3d Particule::getPosition() {
	return position;
}

Vector3d Particule::getDirection() {
	return direction;
}


float Particule::getSpeed() {
	return speed;
}

void Particule::setPosition(Vector3d pos) {
	position = pos;
}

void Particule::setDirection(Vector3d dir) {
	direction = dir;
}


void Particule::setSpeed(float vitesse) {
	speed = vitesse;
}

void Particule::move() {
	position += direction * speed;
}

void Particule::draw() {
	ofDrawIcoSphere(position.v3(), 10);
}