#pragma once
#include "Vec3.h"
#include <vector>
class CollisionManifold
{
public:
	bool colliding;
	Vec3 normal;
	float depth;
	std::vector<Vec3> contacts; //��ײ��
	void Reset();
};