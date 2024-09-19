#pragma once
#include "Vector3d.h"

#ifndef Particule_H
#define Particule_H

class Particule
{

private:
	Vector3d position;
	Vector3d direction;
	float speed;

public:

	Particule();
	Particule(Vector3d pos, Vector3d dir, float speed);
	Particule(const Particule& other);
	~Particule();

	Vector3d getPosition();
	Vector3d getDirection();
	float getSpeed();

	void setPosition(Vector3d pos);
	void setDirection(Vector3d dir);
	void setSpeed(float vitesse);

  	void eulerIntegrate(float t);

	void move();
	void draw();

};

#endif