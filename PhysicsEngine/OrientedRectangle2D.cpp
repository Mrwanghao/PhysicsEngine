#include "OrientedRectangle2D.h"



OrientedRectangle2D::OrientedRectangle2D()
	:
	halfExtents(1.0f, 1.0f),
	rotation(0.0f)
{
}

OrientedRectangle2D::OrientedRectangle2D(const Point2D & _origin, const Vec2 & _halfExtents, float _rotation)
	:
	origin(_origin),
	halfExtents(_halfExtents),
	rotation(_rotation)
{
}


