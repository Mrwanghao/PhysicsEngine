#include "Circle2D.h"

Circle2D::Circle2D()
	:
	radius(1.0f)
{
}

Circle2D::Circle2D(const Point2D & _center, float _radius)
	:
	center(_center),
	radius(_radius)
{
}
