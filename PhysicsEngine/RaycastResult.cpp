#include "RaycastResult.h"

void RaycastResult::Reset()
{
	t = -1;
	hit = false;
	normal = Vec3(0, 0, 1);
	point = Vec3(0, 0, 0);
}
