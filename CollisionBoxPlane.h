#pragma once
#include "Vector3.h"
#include "Particle.h"
#include "ofMain.h"

struct CollisionResult {
    bool hasCollision;
    Vector3 pointOfImpact;
    float penetrationDepth;  
};

class CollisionBoxPlane {
public:
    CollisionBoxPlane(Vector3 planePoint, Vector3 planeNormal);

   
    CollisionResult testCollision(const Particle& center, float width, float height, float depth);

private:
    Vector3 point;    
    Vector3 normal;   

    Vector3 closestPointOnPlane(const Vector3& point) const; 
};
