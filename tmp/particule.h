#pragma once
#include "Vector3.h"

#ifndef PARTICLE_H
#define PARTICLE_H

class Particle
{

private:
	Vector3d position;
	Vector3d direction;
	float speed;

public:

	Particle();
	Particle(Vector3d pos, Vector3d dir, float speed);
	Particle(const Particle& other);
	~Particle();

	Vector3 getPosition();
	Vector3 getDirection();
	float getSpeed();

	void setPosition(Vector3 pos);
	void setDirection(Vector3 dir);
	void setSpeed(float vitesse);

  	void eulerIntegrate(float t);

	void move();
	void draw();

};

#endif
