#pragma once
#include "BoundingBox.h"
#include "RigidBodyBox.h"
#include "consts.h"
#include <vector>
#include <array>
#include <memory>

class OcTree
{
private:
	
	struct Node {
		BoundingBox bounds;
		std::vector<RigidBodyBox* *> objects; //Particules dans le noeuds
		std::unique_ptr<Node> children[8]; //Sous-noeuds
		bool isLeaf;

		Node(const BoundingBox& bounds) : bounds(bounds) {}
	};

	std::unique_ptr<Node> root; // Racine de l'octree

	bool insert(RigidBodyBox* *object, Node* node);
	//On subdivise un noeud en 8 sous-noeuds
	void subdivide(Node* node);

	void drawNode(Node* node);

	void collectLeafNodes(Node* node, std::vector<std::array<RigidBodyBox* *, MAX_POINTS>>& potentialCollisions);

public:

	static const int MAX_POINTS = 2; // Limite de points avant subdivision

	//Constructors
	OcTree();
	OcTree(const BoundingBox& bounds);

	//Insrer une particule dans l'arbre
	bool insert(RigidBodyBox* *object);

	std::vector<std::array<RigidBodyBox* *, MAX_POINTS>> getPotentialCollisions();

	void draw();
};

