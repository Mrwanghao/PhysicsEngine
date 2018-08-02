#include "Rectangle2D.h"
#include <math.h>


Rectangle2D::Rectangle2D()
	:
	size(1.0f, 1.0f)
{
}

Rectangle2D::Rectangle2D(const Point2D & _origin, const Vec2 & _size)
	:
	origin(_origin),
	size(_size)
{
}

Vec2 Rectangle2D::GetMin() const
{
	Vec2 p1 = origin;
	Vec2 p2 = origin + size;

	return Vec2(fminf(p1.x, p2.x), fminf(p1.y, p2.y));
}

Vec2 Rectangle2D::GetMax() const
{
	Vec2 p1 = origin;
	Vec2 p2 = origin + size;

	return Vec2(fmaxf(p1.x, p2.x), fmaxf(p1.y, p2.y));
}

Rectangle2D Rectangle2D::FromMinToMax(const Vec2& min, const Vec2& max) const
{
	return Rectangle2D(min, max - min);
}


