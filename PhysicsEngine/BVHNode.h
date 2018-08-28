#pragma once

#include "AABB.h"


class Mesh;

class BVHNode
{
public:
	AABB bounds;
	BVHNode* children;
	int triangleCount;
	int* triangles;
	BVHNode() : children(0), triangleCount(0), triangles(0) {}
};

void AccelerateMesh(Mesh& mesh);
void SplitBVHNode(BVHNode* node, const Mesh& model, int depth);
void FreeBVHNode(BVHNode* node);