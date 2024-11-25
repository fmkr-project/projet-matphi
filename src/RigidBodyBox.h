#pragma once
#include "RigidBody.h"
class RigidBodyBox : public RigidBody
{
private:
	float height;
	float width;
	float depth;

public:

	RigidBodyBox();
	RigidBodyBox(Particle center, Quaternion orientation, Vector3 angularVelocity, float h, float w, float d);
	RigidBodyBox(const RigidBodyBox& body);
	~RigidBodyBox();

	// Getters
	float getHeight() const;
	float getWidth() const;
	float getDepth() const;
	virtual Sphere getEnclosingSphere() const override;

	// Setters
	void setHeight(float h);
	void setWidth(float w);
	void setDepth(float d);

	virtual void setMomentInertia() override;
	virtual void draw(ofColor color) override;
	virtual void drawEnclosingSphere(ofColor color) override;
};

