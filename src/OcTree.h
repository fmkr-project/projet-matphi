#pragma once
#include "BoundingBox.h"
#include "RigidBody.h"
#include <vector>
#include <memory>

class OcTree
{
private:
	
	struct Node {
		BoundingBox bounds;
		std::vector<RigidBody*> objects; //Particules dans le noeuds
		std::unique_ptr<Node> children[8]; //Sous-noeuds

		Node(const BoundingBox& bounds) : bounds(bounds) {}
	};

	std::unique_ptr<Node> root; // Racine de l'octree

	bool insert(RigidBody* object, Node* node);
	//On subdivise un noeud en 8 sous-noeuds
	void subdivide(Node* node);

public:

	static const int MAX_POINTS = 4; // Limite de points avant subdivision

	//Constructors
	OcTree(const BoundingBox& bounds);

	//Insérer une particule dans l'arbre
	bool insert(RigidBody* object);
};

