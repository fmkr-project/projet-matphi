#pragma once
#include "RigidBody.h"
class RigidBodyBox : public RigidBody
{
private:
	float mass;
	float height;
	float width;
	float depth;

public:

	RigidBodyBox();
	RigidBodyBox(Particle center, Quaternion orientation, Vector3 angularVelocity, float m, float h, float w, float d);
	RigidBodyBox(const RigidBodyBox& body);
	~RigidBodyBox();

	// Getters
	float getMass() const;
	float getHeight() const;
	float getWidth() const;
	float getDepth() const;

	// Setters
	void setMass(const float& m);
	void setHeight(const float& h);
	void setWidth(const float& w);
	void setDepth(const float& d);

	virtual void setMomentInertia() override;
};

