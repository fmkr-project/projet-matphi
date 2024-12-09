#include "BoundingBox.h"
#include <of3dGraphics.h>

BoundingBox::BoundingBox() {
	min = Vector3();
	max = Vector3();
}

BoundingBox::BoundingBox(Vector3 mi, Vector3 ma) {
	min = mi;
	max = ma;
}

BoundingBox::BoundingBox(const BoundingBox& box) {
	min = box.min;
	max = box.max;
}

bool BoundingBox::contains(const RigidBody& object) {

	Vector3 v = object.getCenterMass().getPosition(); //Rcupre le contre de masse de l'objet
	Sphere s = object.getEnclosingSphere();
    float radius = s.getRadius(); // Rayon de la sphre

    // Vrification si le centre de masse est a l'intrieur de la BoundingBox
    bool insideX = (v.getX() >= min.getX()) && (v.getX() <= max.getX());
    bool insideY = (v.getY() >= min.getY()) && (v.getY() <= max.getY());
    bool insideZ = (v.getZ() >= min.getZ()) && (v.getZ() <= max.getZ());

    // Si le centre de masse de l'objet est dans la bounding box
    bool insideCenter = insideX && insideY && insideZ;

    bool intersectsX = (v.getX() + radius >= min.getX()) && (v.getX() - radius <= max.getX());
    bool intersectsY = (v.getY() + radius >= min.getY()) && (v.getY() - radius <= max.getY());
    bool intersectsZ = (v.getZ() + radius >= min.getZ()) && (v.getZ() - radius <= max.getZ());
    bool intersectsBoundingBox = intersectsX && intersectsY && intersectsZ;
    
    
    // L'objet est contenu dans cette BoundingBox si son centre est dedans, ou si la sphere touche les bords
    return insideCenter || intersectsBoundingBox;
}

void BoundingBox::draw() {
    float size = max.getX() - min.getX();
    Vector3 centerOfMass(
        (min.getX() + max.getX()) / 2,
        (min.getY() + max.getY()) / 2,
        (min.getZ() + max.getZ()) / 2
    );


    ofSetColor(ofColor(255, 0, 0));
    ofNoFill();

    ofDrawBox(centerOfMass.v3(), size);
}