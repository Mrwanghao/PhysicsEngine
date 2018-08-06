#include "BoundingShape.h"

BoundingShape::BoundingShape()
	:
	rects(0),
	rectCount(0),
	circles(0),
	circleCount(0)
{
}

BoundingShape::~BoundingShape()
{
	if (circles)
	{
		delete[] circles;
		circles = nullptr;
	}

	if (rects)
	{
		delete[] rects;
		rects = nullptr;
	}
}
