#include "particule.h"
#include <of3dGraphics.h>

Particule::Particule() {
	position = Vector3d();
	direction = Vector3d();
	speed = 0;
	color = ofColor();
}

Particule::Particule(Vector3d pos, Vector3d dir, float spd, ofColor col) {
	position = pos;
	direction = dir;
	speed = spd;
	color = col;
}

Particule::Particule(const Particule& other) {
	position = other.position;
	direction = other.direction;
	speed = other.speed;
	color = other.color;
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

ofColor Particule::getColor() {
	return color;
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

void Particule::setColor(ofColor col) {
	color = col;
}

void Particule::move() {
	position += ofGetLastFrameTime() * direction * speed;
}

void Particule::draw() {
	ofDrawIcoSphere(position.v3(), 1);
}
