#pragma once
#include "Vector3.h"
#include <ofGraphics.h>

#ifndef PARTICULE_H
#define PARTICULE_H

class Particle
{

private:
	Vector3 position;
	Vector3 speed;
	float mass;
	ofColor color;

public:


	Particle();
	Particle(Vector3 pos, Vector3 spd, float m);
	Particle(Vector3 pos, Vector3 spd, float m, ofColor col);
	Particle(const Particle& other);
	~Particle();

	Vector3 getPosition();
	Vector3 getSpeed();
	ofColor getColor();

	float getInverseMass();

	void setPosition(Vector3 pos);
	void setSpeed(Vector3 vitesse);
	void setColor(ofColor col);

	void eulerIntegrate(float t);

	void move();
	void draw();

};

#endif
