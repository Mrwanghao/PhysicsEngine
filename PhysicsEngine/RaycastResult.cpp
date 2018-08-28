#include "RaycastResult.h"

void RaycastResult::Reset()
{
	t = -1;
	hit = false;
	normal = Vec3(0, 0, 1);
	point = Vec3(0, 0, 0);
}

void Reset(RaycastResult * result)
{
	result->t = -1;
	result->hit = false;
	result->normal = Vec3(0, 0, 1);
	result->point = Vec3(0, 0, 0);
}
