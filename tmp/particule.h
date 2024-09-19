#pragma once
#include "vector3d.h"
#include "particule.h"

#ifndef PARTICULE_H
#define PARTICULE_H

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

	void move();
	void draw();

};

#endif

class particule
{
};




