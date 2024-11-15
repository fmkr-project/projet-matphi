#include "RigidBodyBox.h"
#include <of3dGraphics.h>
#include <cmath>

// Constructeurs
RigidBodyBox::RigidBodyBox(Particle center, Quaternion orientation, Vector3 angularVelocity, float m, float h, float w, float d)
    : RigidBody(center, orientation, angularVelocity), mass(m), height(h), width(w), depth(d) {
    setMomentInertia();  // Calcul du moment d'inertie lors de la cration de l'objet
}

RigidBodyBox::RigidBodyBox()
    : RigidBody(), mass(0), height(0), width(0), depth(0) {
    setMomentInertia();  // Calcul du moment d'inertie lors de l'initialisation
}

RigidBodyBox::RigidBodyBox(const RigidBodyBox& other)
    : RigidBody(other), mass(other.mass), height(other.height), width(other.width), depth(other.depth) {
    setMomentInertia();  // Recalcul du moment d'inertie partir des autres paramtres
}

// Destructeur
RigidBodyBox::~RigidBodyBox() {
    // Pas de ressources dynamiques librer, donc ce destructeur peut rester vide
}

// Calcul du moment d'inertie pour une bo�te
void RigidBodyBox::setMomentInertia() {
    float I_x = (1.0f / 12.0f) * mass * (height * height + depth * depth);
    float I_y = (1.0f / 12.0f) * mass * (width * width + depth * depth);
    float I_z = (1.0f / 12.0f) * mass * (height * height + width * width);

    // Cr�er la matrice de moment d'inertie
    Matrix3 res = Matrix3();
    res.setElement(0, 0, I_x);  // Moment d'inertie autour de l'axe X
    res.setElement(1, 1, I_y);  // Moment d'inertie autour de l'axe Y
    res.setElement(2, 2, I_z);  // Moment d'inertie autour de l'axe Z

    // Mettre � jour le moment d'inertie
    momentInertia = res;
}

// Getter pour la masse
float RigidBodyBox::getMass() const {
    return mass;
}

// Setter pour la masse
void RigidBodyBox::setMass(float m) {
    mass = m;
    setMomentInertia();  // Recalculer le moment d'inertie aprs avoir modifi la masse
}

// Getter pour la hauteur
float RigidBodyBox::getHeight() const {
    return height;
}

// Setter pour la hauteur
void RigidBodyBox::setHeight(float h) {
    height = h;
    setMomentInertia();  // Recalculer le moment d'inertie aprs avoir modif la hauteur
}

// Getter pour la largeur
float RigidBodyBox::getWidth() const {
    return width;
}

// Setter pour la largeur
void RigidBodyBox::setWidth(float w) {
    width = w;
    setMomentInertia();  // Recalculer le moment d'inertie aprs avoir modifi la largeur
}

// Getter pour la profondeur
float RigidBodyBox::getDepth() const {
    return depth;
}

// Setter pour la profondeur
void RigidBodyBox::setDepth(float d) {
    depth = d;
    setMomentInertia();  // Recalculer le moment d'inertie apr�s avoir modifi� la profondeur
}

void RigidBodyBox::draw(ofColor color) {
    ofSetColor(color);
    ofDrawBox(centerMass.getPosition().v3(), centerMass.getSize() * 2);
}
