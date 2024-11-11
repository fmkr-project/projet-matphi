#pragma once
#include "Particle.h"
#include "Quaternion.h"
#include "Vector3.h"
#include "Matrix3.h"

class RigidBody
{
private:
    Particle centerMass;
    Quaternion orientation;
    Vector3 angularVelocity;
    

protected:
    Matrix3 momentInertia;

public:
    // Constructeurs
    RigidBody();  
    RigidBody(Particle center, Quaternion orientation, Vector3 angularVelocity);
    RigidBody(const RigidBody& body);  // Constructeur de copie
    virtual ~RigidBody();

    // Getters
    Particle getCenterMass() const;
    Quaternion getOrientation() const;
    Vector3 getAngularVelocity() const;
    Matrix3 getMomentInertia() const;

    // Setters
    void setCenterMass(const Particle& center);
    void setOrientation(const Quaternion& orientation);
    void setAngularVelocity(const Vector3& angularVelocity);

    virtual void setMomentInertia() = 0; 
};
