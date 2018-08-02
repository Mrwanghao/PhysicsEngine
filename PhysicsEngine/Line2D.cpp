#include "Line2D.h"

Line2D::Line2D()
{
}

Line2D::Line2D(const Point2D & _start, const Point2D & _end)
	:
	start(_start),
	end(_end)
{
}

float Line2D::Length() const
{
	return (end - start).Magnitude();
}

float Line2D::LengthSq() const
{
	return (end - start).MagnitudeSq();
}
