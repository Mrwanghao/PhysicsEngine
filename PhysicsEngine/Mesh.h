#pragma once

#include "Triangle.h"
#include "Vec3.h"
#include "BVHNode.h"

class Mesh
{
public:
	int triangleCount;
	union
	{
		float* values;
		Point3D* vertices;
		Triangle* triangles;
	};

	BVHNode * accelerator; 
						   
public:
	Mesh() : triangleCount(0), values(0), accelerator(0) {}
	~Mesh();

};