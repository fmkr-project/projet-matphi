#include "OcTree.h"
#include "BoundingBox.h"
#include <memory>

OcTree::OcTree()
{
    BoundingBox box(Vector3(0, 0, -512), Vector3(1024, 1024, 512));
    root = std::make_unique<Node>(box);
    root->isLeaf = true;
}

OcTree::OcTree(const BoundingBox& box) {
	root = std::make_unique<Node>(box);
}

void OcTree::collectLeafNodes(Node* node, std::vector<std::vector<RigidBodyBox* *>>& potentialCollisions) {
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
    if (isLeaf && node->objects.size() >= 2) {
        // Ajouter le tableau des objets a la liste de collisions potentielles
        std::vector<RigidBodyBox* *> nodeObjects = {};
        for (int i = 0; i < node->objects.size(); ++i) {
            nodeObjects.push_back(node->objects[i]);
        }
        potentialCollisions.push_back(nodeObjects);
    }
}

std::vector<std::vector<RigidBodyBox* *>> OcTree::getPotentialCollisions() {
    std::vector<std::vector<RigidBodyBox* *>> potentialCollisions;

    // Parcours depuis la racine
    if (root) {
        collectLeafNodes(root.get(), potentialCollisions);
    }

    return potentialCollisions;
}

bool OcTree::insert(RigidBodyBox* *object) {
	return insert(object, root.get());
}

bool OcTree::insert(RigidBodyBox** object, Node* node) {
    // Vérifier si l'objet est dans la bounding box du noeud
    if (!node->bounds.contains(**object)) {
        return false;
    }

    // Si le noeud est une feuille et qu'il peut encore contenir des objets
    if (node->isLeaf) {
        node->objects.push_back(object);

        // Si trop d'objets dans le noeud, subdiviser
        if (node->objects.size() > MAX_POINTS) {
            subdivide(node);
        }
        return true;
    }

    // Sinon, essayer d'insérer l'objet dans un sous-nœud
    for (auto& child : node->children) {
        insert(object, child.get());
    }

    return false;
}

// Subdivise un noeud en 8 sous-noeuds
void OcTree::subdivide(Node* node) {
    if ((node->bounds.getMax() - node->bounds.getMin()).magnitude() < 500) return;
    node->isLeaf = false;
    BoundingBox b = node->bounds;
    Vector3 min = b.getMin();
    Vector3 max = b.getMax();

    float midX = (min.getX() + max.getX()) / 2;
    float midY = (min.getY() + max.getY()) / 2;
    float midZ = (min.getZ() + max.getZ()) / 2;

    // Créer les 8 sous-noeuds
    node->children[0] = std::make_unique<Node>(BoundingBox(Vector3(min.getX(), min.getY(), min.getZ()), Vector3(midX, midY, midZ)));
    node->children[1] = std::make_unique<Node>(BoundingBox(Vector3(midX, min.getY(), min.getZ()), Vector3(max.getX(), midY, midZ)));
    node->children[2] = std::make_unique<Node>(BoundingBox(Vector3(min.getX(), midY, min.getZ()), Vector3(midX, max.getY(), midZ)));
    node->children[3] = std::make_unique<Node>(BoundingBox(Vector3(midX, midY, min.getZ()), Vector3(max.getX(), max.getY(), midZ)));
    node->children[4] = std::make_unique<Node>(BoundingBox(Vector3(min.getX(), min.getY(), midZ), Vector3(midX, midY, max.getZ())));
    node->children[5] = std::make_unique<Node>(BoundingBox(Vector3(midX, min.getY(), midZ), Vector3(max.getX(), midY, max.getZ())));
    node->children[6] = std::make_unique<Node>(BoundingBox(Vector3(min.getX(), midY, midZ), Vector3(midX, max.getY(), max.getZ())));
    node->children[7] = std::make_unique<Node>(BoundingBox(Vector3(midX, midY, midZ), Vector3(max.getX(), max.getY(), max.getZ())));

    // Réassigner les objets aux sous-nœuds
    for (auto& obj : node->objects) {
        for (auto& child : node->children) {
            insert(obj, child.get());
        }
    }

    // Vider la liste des objets, ils ont été réinsérés dans les sous-nœuds
    node->objects.clear();
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
