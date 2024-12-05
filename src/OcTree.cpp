#include "OcTree.h"
#include "BoundingBox.h"
#include <memory>

OcTree::OcTree()
{
    BoundingBox box(Vector3(1024, 0, 0), Vector3(0, 1024, -1024));
    root = std::make_unique<Node>(box);
}

OcTree::OcTree(const BoundingBox& box) {
	root = std::make_unique<Node>(box);
}

void OcTree::collectLeafNodes(Node* node, std::vector<std::array<RigidBodyBox*, MAX_POINTS>>& potentialCollisions) {
    if (!node) return;

    // Si le noeud n'a pas d'enfants, c'est une feuille
    bool isLeaf = true;
    for (const auto& child : node->children) {
        if (child) {
            isLeaf = false;
            collectLeafNodes(child.get(), potentialCollisions); // Parcourir les enfants
        }
    }

    // Si c'est une feuille et qu'elle contient des objets, on l'ajoute
    if (isLeaf && !node->objects.empty()) {
        // Ajouter le tableau des objets a la liste de collisions potentielles
        std::array<RigidBodyBox*, MAX_POINTS> nodeObjects = {};
        for (int i = 0; i < node->objects.size(); ++i) {
            nodeObjects[i] = node->objects[i];
        }
        potentialCollisions.push_back(nodeObjects);
    }
}

std::vector<std::array<RigidBodyBox*, OcTree::MAX_POINTS>> OcTree::getPotentialCollisions() {
    std::vector<std::array<RigidBodyBox*, MAX_POINTS>> potentialCollisions;

    // Parcours depuis la racine
    if (root) {
        collectLeafNodes(root.get(), potentialCollisions);
    }

    return potentialCollisions;
}

bool OcTree::insert(RigidBodyBox* object) {
	return insert(object, root.get());
}

bool OcTree::insert(RigidBodyBox* object, Node* node) {

    Particle centerMass = object->getCenterMass();
    // Verifier si la particule est dans la bounding box du noeud
    if (!node->bounds.contains(*object)){
        return false; 
    }

    // Si le noeud a atteint sa capacit maximale de particules
    if (node->objects.size() >= MAX_POINTS) {
        if (node->children[0] == nullptr) { // Si les sous-noeuds n'existent pas encore
            subdivide(node); // Divise le nud en sous-nuds
        }

        // Tenter d'inserer la particule dans l'un des sous-noeuds
        for (auto& child : node->children) {
            if (child && insert(object, child.get())) {
                return true;
            }
        }
    }
    else {
        // Si la particule peut etre insere ici (le noeud n'est pas plein)
        node->objects.push_back(object);
        return true;
    }
    return false; // Retourner false si l'insertion a echoue
}

// Subdivise un noeud en 8 sous-noeuds
void OcTree::subdivide(Node* node) {
    std::cout << "Here !!" << std::endl;
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

void OcTree::draw() {
    // Appeler la fonction draw pour le noeud racine
    drawNode(root.get());
}

void OcTree::drawNode(Node* node) {
    // Dessiner la bounding box du noeud actuel
    node->bounds.draw();  // Utilisez une couleur appropriee

    // Verifier si le noeud a des enfants
    for (auto& child : node->children) {
        if (child) {
            // Dessiner recursivement pour chaque enfant
            drawNode(child.get());
        }
    }
}
