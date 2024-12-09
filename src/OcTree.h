#pragma once
#include "BoundingBox.h"
#include "RigidBodyBox.h"
#include "consts.h"
#include <vector>
#include <memory>

class OcTree
{
private:
	
	struct Node {
		BoundingBox bounds;
		std::vector<RigidBodyBox* *> objects; //Solides dans le noeuds
		std::unique_ptr<Node> children[8]; //Sous-noeuds
		bool isLeaf;

		Node(const BoundingBox& bounds) : bounds(bounds), isLeaf(true) {}
	};

	std::unique_ptr<Node> root; // Racine de l'octree

	bool insert(RigidBodyBox* *object, Node* node);
	//On subdivise un noeud en 8 sous-noeuds
	void subdivide(Node* node);

	void drawNode(Node* node);

	void collectLeafCollisions(Node* node, std::vector<std::vector<RigidBodyBox* *>>& potentialCollisions);

public:

	static const int MAX_POINTS = 2; // Limite de points avant subdivision

	//Constructors
	OcTree();
	OcTree(const BoundingBox& bounds);

	//Insrer une particule dans l'arbre
	bool insert(RigidBodyBox* *object);

	std::vector<std::vector<RigidBodyBox* *>> getPotentialCollisions();

	void draw();
};

