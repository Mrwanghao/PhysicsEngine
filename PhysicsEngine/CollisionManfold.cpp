#include "CollisionManfold.h"

void CollisionManifold::Reset()
{
	colliding = false;
	normal = Vec3(0, 0, 1);
	depth = FLT_MAX;
	if (contacts.size() > 0) {
		contacts.clear();
	}
}
