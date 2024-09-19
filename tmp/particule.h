#pragma once
#include "vector3d.h"
#include <ofGraphics.h>

#ifndef PARTICULE_H
#define PARTICULE_H

class Particule
{

private:
	Vector3d position;
	Vector3d speed;
	float mass;
	ofColor color;

public:


	Particule();
	Particule(Vector3d pos, Vector3d spd, float m);
	Particule(Vector3d pos, Vector3d spd, float m, ofColor col);
	Particule(const Particule& other);
	~Particule();

	Vector3d getPosition();
	Vector3d getSpeed();
	ofColor getColor();

	float getInverseMass();

	void setPosition(Vector3d pos);
	void setSpeed(Vector3d vitesse);
	void setColor(ofColor col);

	void eulerIntegrate(float t);

	void move();
	void draw();

};

#endif
