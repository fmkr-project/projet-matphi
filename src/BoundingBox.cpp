#include "BoundingBox.h"

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

	Vector3 v = object.getCenterMass().getPosition(); //Récupére le contre de masse de l'objet
	Sphere s = object.getEnclosingSphere();
    float radius = s.getRadius(); // Rayon de la sphère

    // Vérification si le centre de masse est à l'intérieur de la BoundingBox
    bool insideX = v.getX() >= min.getX() && v.getX() <= max.getX();
    bool insideY = v.getY() >= min.getY() && v.getY() <= max.getY();
    bool insideZ = v.getZ() >= min.getZ() && v.getZ() <= max.getZ();

    // Si le centre de masse de l'objet est dans la bounding box
    bool insideCenter = insideX && insideY && insideZ;

    // Vérification si la sphère dépasse les limites de la BoundingBox
    bool overlapsX = v.getX() - radius < min.getX() || v.getX() + radius > max.getX();
    bool overlapsY = v.getY() - radius < min.getY() || v.getY() + radius > max.getY();
    bool overlapsZ = v.getZ() - radius < min.getZ() || v.getZ() + radius > max.getZ();

    // L'objet est contenu dans cette BoundingBox si son centre est dedans, ou si la sphère touche les bords
    return insideCenter || (overlapsX || overlapsY || overlapsZ);
}