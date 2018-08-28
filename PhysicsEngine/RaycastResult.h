#pragma once


#include "Vec3.h"



class RaycastResult
{
public:
	Vec3 point;
	Vec3 normal;
	float t;
	bool hit;

	void Reset();
};

void Reset(RaycastResult* result);



