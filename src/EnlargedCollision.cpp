#include "EnlargedCollision.h"

EnlargedCollision::EnlargedCollision()
{
	octree = OcTree();
	collisionManager = CollisionManager();
}

std::vector<RigidBodyBox*> EnlargedCollision::checkCollision(std::vector<RigidBodyBox*> myBoxes)
{
	std::vector<RigidBodyBox*> *final = new std::vector<RigidBodyBox*>();
	
	octree = OcTree();
	for (size_t i = 0; i < myBoxes.size(); i++)
	{
		octree.insert(&myBoxes[i]);
	}

	std::vector<std::array<RigidBodyBox* *, MAX_POINTS>> potentialCollisions = octree.getPotentialCollisions();
	std::vector<RigidBodyBox*> *otherBoxes = new std::vector<RigidBodyBox*>();
	for (size_t i = 0; i < myBoxes.size(); i++)
	{
		bool boxHasCollision = false;
		for (size_t j = 0; j < potentialCollisions.size(); j++)
		{
			if (!potentialCollisions[j][1]) continue;
			for (size_t k = 0; k < potentialCollisions[j].size(); k++)
			{
				if (myBoxes[i] == *potentialCollisions[j][k]) boxHasCollision = true;
			}
		}

		if (!boxHasCollision) otherBoxes->push_back(myBoxes[i]);
	}
	
	for (size_t i = 0; i < potentialCollisions.size(); i++)
	{
		std::array<RigidBodyBox* *, MAX_POINTS> rigidBodies = potentialCollisions[i];
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
						collisionManager.detect_collisions();
						final->push_back(*rigidBodies[j]);
						final->push_back(*rigidBodies[k]);
						collisionManager.clear_cubes();
					}
				}
			}
		}
	}

	for (size_t i = 0; i < otherBoxes->size(); i++)
		final->push_back((*otherBoxes)[i]);
	std::cout << final->size() << std::endl;
	return *final;
}

OcTree& EnlargedCollision::getOcTree()
{
	return octree;
}
