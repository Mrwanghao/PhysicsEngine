#include "Triangle.h"



Triangle::Triangle()
{
}

Triangle::Triangle(const Point3D & p1, const Point3D & p2, const Point3D & p3)
	:
	a(p1),
	b(p2),
	c(p3)
{
}


Triangle::~Triangle()
{
}
