#pragma once
#include "vector3d.h"
#include <ofGraphics.h>

#ifndef PARTICULE_H
#define PARTICULE_H

class Particule
{

private:
	Vector3d position;
	Vector3d direction;
	float speed;
	ofColor color;
	float mass;

public:


	Particule();
	Particule(Vector3d pos, Vector3d dir, float speed, ofColor col);
	Particule(const Particule& other);
	~Particule();

	Vector3d getPosition();
	Vector3d getDirection();
	float getSpeed();
	ofColor getColor();

	float getInverseMass();

	void setPosition(Vector3d pos);
	void setDirection(Vector3d dir);
	void setSpeed(float vitesse);
	void setColor(ofColor col);

	void eulerIntegrate(float t);

	void move();
	void draw();

};

#endif
