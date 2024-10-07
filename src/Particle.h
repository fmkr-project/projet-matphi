#pragma once
#include "Vector3.h"
#include <ofGraphics.h>

#ifndef PARTICULE_H
#define PARTICULE_H

class Particle
{

private:
	Vector3 position;
	Vector3 previousPosition;
	Vector3 speed;
	float mass;
	float size;
	ofColor color;
	Vector3 accumForce;

public:

	Particle();
	Particle(Vector3 pos, Vector3 spd, float m, float s);
	Particle(Vector3 pos, Vector3 spd, float m, float s, ofColor col);
	Particle(const Particle& other);
	~Particle();

	Vector3 getPosition();
	Vector3 getSpeed();
	ofColor getColor();
	float getSize();

	float getInverseMass();

	void setPosition(Vector3 pos);
	void setSpeed(Vector3 vitesse);
	void setColor(ofColor col);
	void setSize(float s);

	void eulerIntegrate(float t);
	void verletIntegrate(float t);

	void move();
	void draw();

	void addForce(const Vector3& force);
	void clearAccum();

	bool operator==(const Particle& p) const;

};

#endif
