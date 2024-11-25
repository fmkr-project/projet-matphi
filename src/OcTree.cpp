#include "OcTree.h"
#include "BoundingBox.h"
#include <memory>

OcTree::OcTree(const BoundingBox& box) {
	root = std::make_unique<Node>(box);
}

bool OcTree::insert(RigidBody* object) {
	return insert(object, root.get());
}

bool OcTree::insert(RigidBody* object, Node* node) {

    Particle centerMass = object->getCenterMass();
    // Vérifier si la particule est dans la bounding box du nœud
    if (!node->bounds.contains(*object)){
        return false; 
    }

    // Si le nœud a atteint sa capacité maximale de particules
    if (node->objects.size() >= MAX_POINTS) {
        if (node->children[0] == nullptr) { // Si les sous-nœuds n'existent pas encore
            subdivide(node); // Divise le nœud en sous-nœuds
        }

        // Tenter d'insérer la particule dans l'un des sous-nœuds
        for (auto& child : node->children) {
            if (child && insert(object, child.get())) {
                return true;
            }
        }
    }
    else {
        // Si la particule peut être insérée ici (le nœud n'est pas plein)
        node->objects.push_back(object);
        return true;
    }
    return false; // Retourner false si l'insertion a échoué
}

// Subdivise un nœud en 8 sous-nœuds
void OcTree::subdivide(Node* node) {
    BoundingBox b = node->bounds;
    Vector3 min = b.getMin();
    Vector3 max = b.getMax();

    float midX = (min.getX() + max.getX()) / 2;
    float midY = (min.getY() + max.getY()) / 2;
    float midZ = (min.getZ() + max.getZ()) / 2;

    node->children[0] = std::make_unique<Node>(BoundingBox(Vector3(min.getX(), min.getY(), min.getZ()), Vector3(midX, midY, midZ)));
    node->children[1] = std::make_unique<Node>(BoundingBox(Vector3(midX, min.getY(), min.getZ()), Vector3(max.getX(), midY, midZ)));
    node->children[2] = std::make_unique<Node>(BoundingBox(Vector3(min.getX(), midY, min.getZ()), Vector3(midX, max.getY(), midZ)));
    node->children[3] = std::make_unique<Node>(BoundingBox(Vector3(midX, midY, min.getZ()), Vector3(max.getX(), max.getY(), midZ)));
    node->children[4] = std::make_unique<Node>(BoundingBox(Vector3(min.getX(), min.getY(), midZ), Vector3(midX, midY, max.getZ())));
    node->children[5] = std::make_unique<Node>(BoundingBox(Vector3(midX, min.getY(), midZ), Vector3(max.getX(), midY, max.getZ())));
    node->children[6] = std::make_unique<Node>(BoundingBox(Vector3(min.getX(), midY, midZ), Vector3(midX, max.getY(), max.getZ())));
    node->children[7] = std::make_unique<Node>(BoundingBox(Vector3(midX, midY, midZ), Vector3(max.getX(), max.getY(), max.getZ())));
}