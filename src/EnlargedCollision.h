#pragma once

#include "CollisionManager.h"
#include "OcTree.h"

class EnlargedCollision
{
private:
	OcTree octree;
	CollisionManager collisionManager;

public:
	//Constructeurs
	EnlargedCollision();

	void checkCollision(std::vector<RigidBodyBox*> *);

	OcTree& getOcTree();
};