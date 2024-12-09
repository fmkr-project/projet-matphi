#include "EnlargedCollision.h"

EnlargedCollision::EnlargedCollision()
{
	octree = OcTree();
	collisionManager = CollisionManager();
}

std::vector<RigidBodyBox*> EnlargedCollision::checkCollision(std::vector<RigidBodyBox*> myBoxes, double t)
{
	//std::cout << "before: " << myBoxes.size() << std::endl;
	std::vector<RigidBodyBox*> *final = new std::vector<RigidBodyBox*>();
	
	octree = OcTree();
	for (size_t i = 0; i < myBoxes.size(); i++)
	{
		octree.insert(&myBoxes[i]);
	}

	std::vector<std::vector<RigidBodyBox* *>> potentialCollisions = octree.getPotentialCollisions();
	std::vector<RigidBodyBox*> *otherBoxes = new std::vector<RigidBodyBox*>();
	/*for (size_t i = 0; i < myBoxes.size(); i++)
	{
		bool boxHasCollision = false;
		for (size_t j = 0; j < potentialCollisions.size(); j++)
		{
			//std::cout << potentialCollisions[j].size() << std::endl;
			if (!&potentialCollisions[j]) continue;
			if (!potentialCollisions[j][1]) continue;
			for (size_t k = 0; k < potentialCollisions[j].size(); k++)
			{
				if (!potentialCollisions[j][k]) continue;
				if (myBoxes[i] == *potentialCollisions[j][k]) boxHasCollision = true;
			}
		}
		std::cout << boxHasCollision << std::endl;
		if (!boxHasCollision) final->push_back(myBoxes[i]);
	}*/
	
	for (size_t i = 0; i < potentialCollisions.size(); i++)
	{
		std::vector<RigidBodyBox**> rigidBodies = potentialCollisions[i];
		for (size_t j = 0; j < rigidBodies.size(); j++) {
			for (size_t k = j + 1; k < rigidBodies.size(); k++) {
				if (rigidBodies[j] && rigidBodies[k] && (rigidBodies[j] != rigidBodies[k])) {
					Sphere firstSphere = (*rigidBodies[j])->getEnclosingSphere();
					Sphere secondSphere = (*rigidBodies[k])->getEnclosingSphere();
					float dist = Particle::distance(firstSphere.getCenter(), secondSphere.getCenter());
					if (dist < (firstSphere.getRadius() + secondSphere.getRadius())) {
						std::cout << "ow" << std::endl;
						collisionManager.add_cube(*rigidBodies[j]);
						collisionManager.add_cube(*rigidBodies[k]);
						collisionManager.detect_collisions(t);
						//final->push_back(*rigidBodies[j]);
						//final->push_back(*rigidBodies[k]);
						collisionManager.clear_cubes();
					}
				}
			}
		}
	}
	
	return myBoxes;
}

OcTree& EnlargedCollision::getOcTree()
{
	return octree;
}
