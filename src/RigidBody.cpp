#include "RigidBody.h"
#include "Particle.h"
#include "Quaternion.h"
#include "Vector3.h"

RigidBody::RigidBody() {
	center = Particle();
	orientation = Quaternion(1,0,0,0);
	angularVelocity = Vector3();
}

RigidBody::RigidBody(Particle p, Quaternion q, Vector3 v) {
	center = p;
	orientation = q;
	angularVelocity = v;
}

RigidBody::RigidBody(const RigidBody& body) {
	center = body.center;
	orientation = body.orientation;
	angularVelocity = body.angularVelocity;
}

RigidBody::~RigidBody() {

}