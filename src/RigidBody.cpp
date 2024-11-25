#include "RigidBody.h"

#include "consts.h"
#include "ofAppRunner.h"

// Constructeur par dfaut
RigidBody::RigidBody()
    : centerMass(Particle()), orientation(Quaternion()), angularVelocity(Vector3()), momentInertia(Matrix3()) {}

// Constructeur parametre
RigidBody::RigidBody(Particle center, Quaternion orientation, Vector3 angularVelocity)
    : centerMass(center), orientation(orientation), angularVelocity(angularVelocity) {
    setMomentInertia(); 
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

Sphere RigidBody::getEnclosingSphere() const
{
    return Sphere();
}

// Physics
void RigidBody::move()
{
    centerMass.addForce(centerMass.getMass() * g);

    float deltaTime = ofGetLastFrameTime();

    integratePosition(deltaTime);
    integrateRotation(deltaTime);
    centerMass.clearAccum();
}

void RigidBody::integratePosition(float deltaTime)
{
    centerMass.eulerIntegrate(deltaTime);
}

void RigidBody::integrateRotation(float deltaTime)
{
    Quaternion omega = *new Quaternion(angularVelocity, 0);
    orientation = Quaternion::Normalize(orientation + omega * orientation * 0.5 * deltaTime);
}

void RigidBody::applyForceAt(const Vector3 force, const Vector3 applyPosition, const float deltaTime)
{
    Vector3 l = applyPosition - centerMass.getPosition();
    
    // Modify acceleration
    //float alpha = Vector3::angle(l, force);
    centerMass.addForce(force);
    
    // Induce rotation
    Quaternion a = Quaternion::Normalize(orientation);
    Matrix3 r = Quaternion::ToRotationMatrix(a);
    Matrix3 rInverse = r.inverse();
    
    Vector3 torque = l * force;
    Matrix3 moment = getMomentInertia();
    Matrix3 momentInverse = moment.inverse();
    Vector3 angularAcceleration = torque * momentInverse;

    angularVelocity += angularAcceleration * deltaTime;
/*
    // Update J
    Matrix3 jMinusOne = r * momentInverse * rInverse;
    Matrix3 j = jMinusOne.inverse();
    setMomentInertia(j);*/
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

void RigidBody::setMomentInertia(const Matrix3& momentInertia) {
    this->momentInertia = momentInertia;
}

void RigidBody::setMomentInertia() {

}

void RigidBody::draw(ofColor) {
}
