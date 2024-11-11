#include "RigidBodyBox.h"
#include <cmath>


RigidBodyBox::RigidBodyBox(Particle center, Quaternion orientation, Vector3 angularVelocity, float m, float h, float w, float d)
	: RigidBody(center, orientation, angularVelocity), mass(m), height(h), width(w), depth(d) {
	setMomentInertia();
}

void RigidBodyBox::setMomentInertia() {
	float tmp1 = 1 / 12 * mass * (sqrt(height) + sqrt(depth));
	float tmp2 = 1 / 12 * mass * (sqrt(height) + sqrt(width));
	float tmp3 = 1 / 12 * mass * (sqrt(depth) + sqrt(width));

	Matrix3 res = Matrix3();
	res.setElement(0, 0, tmp1);
	res.setElement(1, 1, tmp2);
	res.setElement(2, 2, tmp3);

	momentInertia = res;
}