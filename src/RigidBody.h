#pragma once
#include "Particle.h"
#include "Quaternion.h"
#include "Vector3.h"
#include "Matrix3.h"

class RigidBody
{
protected:
    Particle centerMass;
    Quaternion orientation;
    Vector3 angularVelocity;

    Vector3 totalForces;

    void integratePosition(float deltaTime);
    void integrateRotation(float deltaTime);
    
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

    // Physics
    void move();
    void applyForceAt(const Vector3 force, const Vector3 applyPosition, const float deltaTime);
    
    // Mthode virtuelle pure pour calculer le moment d'inertie, redfinir dans les classes enfants
    virtual void setMomentInertia() = 0; 

    virtual void draw(ofColor color);
};
