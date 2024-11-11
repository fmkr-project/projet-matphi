#include "RigidBody.h"

// Constructeur par dfaut
RigidBody::RigidBody()
    : centerMass(Particle()), orientation(Quaternion()), angularVelocity(Vector3()), momentInertia(Matrix3()) {}

// Constructeur paramtr
RigidBody::RigidBody(Particle center, Quaternion orientation, Vector3 angularVelocity)
    : centerMass(center), orientation(orientation), angularVelocity(angularVelocity) {
    setMomentInertia();  // Calcul du moment d'inertie lors de la cration de l'objet
}

// Constructeur de copie
RigidBody::RigidBody(const RigidBody& body)
    : centerMass(body.centerMass), orientation(body.orientation), angularVelocity(body.angularVelocity), momentInertia(body.momentInertia) {}

// Destructeur
RigidBody::~RigidBody() {}

// Getters
Particle RigidBody::getCenterMass() const {
    return centerMass;
}

Quaternion RigidBody::getOrientation() const {
    return orientation;
}

Vector3 RigidBody::getAngularVelocity() const {
    return angularVelocity;
}

Matrix3 RigidBody::getMomentInertia() const {
    return momentInertia;
}

// Setters
void RigidBody::setCenterMass(const Particle& center) {
    centerMass = center;
}

void RigidBody::setOrientation(const Quaternion& orientation) {
    this->orientation = orientation;
}

void RigidBody::setAngularVelocity(const Vector3& angularVelocity) {
    this->angularVelocity = angularVelocity;
}
