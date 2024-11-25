#pragma once
#include "Particle.h"
#include "Plane.h"
#include <vector>
#include <memory>

class BSPTree
{

private:
	
	struct node {
		Plane plane;
		std::vector<Particle> particles;
		std::unique_ptr<node> plus;
		std::unique_ptr<node> minus;

		node(const Plane& p) : plane(p), plus(nullptr), minus(nullptr) {}
	};

	
};

