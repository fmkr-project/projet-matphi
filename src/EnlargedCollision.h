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

	std::vector<RigidBodyBox*> checkCollision(std::vector<RigidBodyBox*>, double t);

	OcTree& getOcTree();
};