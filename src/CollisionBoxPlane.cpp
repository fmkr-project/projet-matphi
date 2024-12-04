#include "CollisionBoxPlane.h"
#include "Vector3.h"

CollisionBoxPlane::CollisionBoxPlane(Vector3 planePoint, Vector3 planeNormal)
    : point(planePoint), normal(planeNormal.normalized()) {}

Vector3 CollisionBoxPlane::closestPointOnPlane(const Vector3& p) const {
    // Projeter le point sur le plan
    float signedDistance = normal.dotProduct(p - point);
    return p - normal * signedDistance;
}

CollisionResult CollisionBoxPlane::testCollision(const Particle& center, float width, float height, float depth) {
    CollisionResult result;
    result.hasCollision = false;
    result.penetrationDepth = 0.0f;

    // Rcuprer les sommets de la bote
    Vector3 boxMin = center.getPosition() - Vector3(width / 2, height / 2, depth / 2);
    Vector3 boxMax = center.getPosition() + Vector3(width / 2, height / 2, depth / 2);

    // Vrifier chaque sommet de la bote
    for (float x : {boxMin.getX(), boxMax.getX()}) {
        for (float y : {boxMin.getY(), boxMax.getY()}) {
            for (float z : {boxMin.getZ(), boxMax.getZ()}) {
                Vector3 vertex(x, y, z);
                float signedDistance = normal.dotProduct(vertex - point);

                if (signedDistance <= 0) {  // Collision dtecte si sommet sous le plan
                    result.hasCollision = true;
                    result.penetrationDepth = std::max(result.penetrationDepth, -signedDistance);  // Accumuler la profondeur
                    result.pointOfImpact = closestPointOnPlane(vertex);  // Calculer le point d'impact
                }
            }
        }
    }
    return result;
}
