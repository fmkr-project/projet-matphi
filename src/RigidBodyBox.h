#pragma once
#include "RigidBody.h"


struct CollisionBoxResult {
	bool hasCollision;
	std::vector<Vector3> contactPoints;
	float penetrationDepth;
	Vector3 collisionNormal;
};

class RigidBodyBox : public RigidBody
{
private:
	float height;
	float width;
	float depth;

public:

	static CollisionBoxResult testCollision(const RigidBodyBox& a, const RigidBodyBox& other);
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


	std::vector<Vector3> getVertices() const;
	std::vector<Vector3> getAxes() const;
	void projectVerticesOnAxis(const std::vector<Vector3>& vertices, const Vector3& axis, float& min, float& max) const;
	bool overlapsOnAxis(const RigidBodyBox& other, const Vector3& axis, float& penetration, Vector3& collisionNormal, std::vector<Vector3>& contactPoints) const;
};

