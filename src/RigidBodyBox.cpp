#include "RigidBodyBox.h"
#include <of3dGraphics.h>
#include <cmath>

// Constructeurs
RigidBodyBox::RigidBodyBox(Particle center, Quaternion orientation, Vector3 angularVelocity, float h, float w, float d)
    : RigidBody(center, orientation, angularVelocity), height(h), width(w), depth(d) {
    setMomentInertia();  // Calcul du moment d'inertie lors de la cration de l'objet
}

RigidBodyBox::RigidBodyBox()
    : RigidBody(), height(0), width(0), depth(0) {
    setMomentInertia();  // Calcul du moment d'inertie lors de l'initialisation
}

RigidBodyBox::RigidBodyBox(const RigidBodyBox& other)
    : RigidBody(other), height(other.height), width(other.width), depth(other.depth) {
    setMomentInertia();  // Recalcul du moment d'inertie partir des autres paramtres
}

// Destructeur
RigidBodyBox::~RigidBodyBox() {
    // Pas de ressources dynamiques liberer, donc ce destructeur peut rester vide
}

// Calcul du moment d'inertie pour une bote
void RigidBodyBox::setMomentInertia() {
    float I_x = (1.0f / 12.0f) * centerMass.getMass() * (height * height + depth * depth);
    float I_y = (1.0f / 12.0f) * centerMass.getMass() * (width * width + depth * depth);
    float I_z = (1.0f / 12.0f) * centerMass.getMass() * (height * height + width * width);

    // Crer la matrice de moment d'inertie
    Matrix3 res = Matrix3();
    res.setElement(0, 0, I_x);  // Moment d'inertie autour de l'axe X
    res.setElement(1, 1, I_y);  // Moment d'inertie autour de l'axe Y
    res.setElement(2, 2, I_z);  // Moment d'inertie autour de l'axe Z

    // Mettre jour le moment d'inertie
    momentInertia = res;
}

// Getter pour la hauteur
float RigidBodyBox::getHeight() const {
    return height;
}

// Setter pour la hauteur
void RigidBodyBox::setHeight(float h) {
    height = h;
    setMomentInertia();  // Recalculer le moment d'inertie apres avoir modif la hauteur
}

// Getter pour la largeur
float RigidBodyBox::getWidth() const {
    return width;
}

// Setter pour la largeur
void RigidBodyBox::setWidth(float w) {
    width = w;
    setMomentInertia();  // Recalculer le moment d'inertie apres avoir modifi la largeur
}

// Getter pour la profondeur
float RigidBodyBox::getDepth() const {
    return depth;
}

Sphere RigidBodyBox::getEnclosingSphere() const
{
    Particle p = centerMass;
    float r = sqrtf(powf(height, 2) + powf(width, 2) + powf(depth, 2) ) / 2.f;
    return Sphere(p, r);
}

// Setter pour la profondeur
void RigidBodyBox::setDepth(float d) {
    depth = d;
    setMomentInertia();  // Recalculer le moment d'inertie apres avoir modifie la profondeur
}

void RigidBodyBox::draw(ofColor color) {
    ofSetColor(color);
    ofNoFill();

    // Sauvegarde de l'tat de transformation
    ofPushMatrix();

    // Dplacement vers la position de la bote
    ofTranslate(centerMass.getPosition().v3());

    // Rcupration de l'orientation (quaternion)
    Quaternion oriente = orientation; 
    Vector3 axis;
    float angle;
    oriente.toAxisAngle(axis, angle); 

    // Appliquer la rotation avec ofRotateDeg
    ofRotateDeg(angle, axis.getY(), -axis.getX(), axis.getZ()); 

    // Dessiner la bote centre l'origine locale
    ofDrawBox(glm::vec3(0, 0, 0),width,height,depth);

    // Restauration de l'tat de transformation
    ofPopMatrix();
}

void RigidBodyBox::drawEnclosingSphere(ofColor color)
{
    ofSetColor(color);
    ofDrawIcoSphere(centerMass.getPosition().v3(), getEnclosingSphere().getRadius());
}


std::vector<Vector3> RigidBodyBox::getVertices() const {
    std::vector<Vector3> vertices;

    
    std::vector<Vector3> localVertices = {
        { width / 2,  height / 2,  depth / 2},
        { width / 2,  height / 2, -depth / 2},
        { width / 2, -height / 2,  depth / 2},
        { width / 2, -height / 2, -depth / 2},
        {-width / 2,  height / 2,  depth / 2},
        {-width / 2,  height / 2, -depth / 2},
        {-width / 2, -height / 2,  depth / 2},
        {-width / 2, -height / 2, -depth / 2},
    };

    
    for (const auto& vertex : localVertices) {
        Vector3 transformedVertex = orientation.rotate(vertex) + centerMass.getPosition();
        vertices.push_back(transformedVertex);
    }

    return vertices;
}


std::vector<Vector3> RigidBodyBox::getAxes() const {
    return {
        orientation.rotate(Vector3(1, 0, 0)), 
        orientation.rotate(Vector3(0, 1, 0)),  
        orientation.rotate(Vector3(0, 0, 1))   
    };
}



void RigidBodyBox::projectVerticesOnAxis(const std::vector<Vector3>& vertices, const Vector3& axis, float& min, float& max) const {
    min = max = axis.dotProduct(vertices[0]);  
    for (const auto& vertex : vertices) {
        float projection = axis.dotProduct(vertex);
        if (projection < min) min = projection;
        if (projection > max) max = projection;
    }
}


bool RigidBodyBox::overlapsOnAxis(const RigidBodyBox& other, const Vector3& axis, float& penetration, Vector3& collisionNormal) const {
    float min1, max1, min2, max2;

   
    projectVerticesOnAxis(getVertices(), axis, min1, max1);
    projectVerticesOnAxis(other.getVertices(), axis, min2, max2);

    
    if (max1 < min2 || max2 < min1) {
        return false; 
    }

    
    float overlap = std::min(max1, max2) - std::max(min1, min2);
    if (overlap < penetration) {
        penetration = overlap;
        collisionNormal = axis;
    }

    return true;
}


CollisionBoxResult RigidBodyBox::testCollision(const RigidBodyBox& a, const RigidBodyBox& other)
{
    CollisionBoxResult result;
    result.hasCollision = true;  
    result.penetrationDepth = std::numeric_limits<float>::max();

    
    std::vector<Vector3> axes1 = a.getAxes();
    std::vector<Vector3> axes2 = other.getAxes();

    
    for (const auto& axis1 : axes1) {
        for (const auto& axis2 : axes2) {
            axes1.push_back(axis1.crossProduct(axis2).normalized());
        }
    }

  
    for (const auto& axis : axes1) {
        float penetration = std::numeric_limits<float>::max();
        Vector3 collisionNormal;

        if (!a.overlapsOnAxis(other, axis, penetration, collisionNormal)) {
            result.hasCollision = false;  
            return result;
        }

        
        if (penetration < result.penetrationDepth) {
            result.penetrationDepth = penetration;
            result.collisionNormal = collisionNormal;
        }
    }



    return result;
}
