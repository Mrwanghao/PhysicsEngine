#include "OBB.h"
#include "MathUtil.h"


OBB::OBB()
	:
	size(1.0f, 1.0f, 1.0f)
{
	orientation = Rot3x3(0.0f, 0.0f, 0.0f);
}

OBB::OBB(const Point3D & _origin, const Vec3 & _size)
	:
	origin(_origin),
	size(_size)
{
	orientation = Rot3x3(45.0f, 0.0f, 0.0f);
}

OBB::OBB(const Point3D & _origin, const Vec3 & _size, const Matrix3 & _orientation)
	:
	origin(_origin),
	size(_size),
	orientation(_orientation)
{
}


OBB::~OBB()
{
}
