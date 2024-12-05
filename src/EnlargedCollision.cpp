#include "EnlargedCollision.h"

EnlargedCollision::EnlargedCollision()
{
	octree = OcTree();
	collisionManager = CollisionManager();
}

void EnlargedCollision::checkCollision(std::vector<RigidBodyBox*> myBoxes)
{
	octree = OcTree();
	for (size_t i = 0; i < myBoxes.size(); i++)
	{
		octree.insert(myBoxes[i]);
	}

	std::vector<std::array<RigidBodyBox*, MAX_POINTS>> potentialCollisions = octree.getPotentialCollisions();
	for (size_t i = 0; i < potentialCollisions.size(); i++)
	{
		std::array<RigidBodyBox*, MAX_POINTS> rigidBodies = potentialCollisions[i];
		for (size_t j = 0; j < rigidBodies.size(); j++) {
			for (size_t k = j + 1; k < rigidBodies.size(); k++) {
				if (rigidBodies[j] && rigidBodies[k]) {
					Sphere firstSphere = rigidBodies[j]->getEnclosingSphere();
					Sphere secondSphere = rigidBodies[k]->getEnclosingSphere();
					float dist = Particle::distance(firstSphere.getCenter(), secondSphere.getCenter());
					if (dist < (firstSphere.getRadius() + secondSphere.getRadius())) {
						collisionManager.add_cube(rigidBodies[j]);
						collisionManager.add_cube(rigidBodies[k]);
						collisionManager.detect_collisions();
						collisionManager.clear_cubes();
					}
				}
			}
		}
	}
}

OcTree& EnlargedCollision::getOcTree()
{
	return octree;
}
