#pragma once
#include "Vector3.h"

#ifndef PARTICLE_H
#define PARTICLE_H

class Particle
{

private:
	Vector3 position;
	Vector3 direction;
	Vector3 speed;
	float mass;

public:

	Particle();
	Particle(Vector3 pos, Vector3 dir, Vector3 spd, float m);
	Particle(const Particle& other);
	~Particle();

	Vector3 getPosition();
	Vector3 getDirection();
	Vector3 getSpeed();
	float getInverseMass();

	void setPosition(Vector3 pos);
	void setDirection(Vector3 dir);
	void setSpeed(Vector3 vitesse);

  	void eulerIntegrate(float t);

	void move();
	void draw();

};

#endif
