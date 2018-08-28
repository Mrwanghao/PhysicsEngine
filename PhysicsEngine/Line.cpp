#include "Line.h"

Line::Line()
	:
	start(0.0f, 0.0f, 0.0f),
	end(0.0f, 0.0f, 1.0f)
{
}

Line::Line(const Point3D & _start, const Point3D & _end)
	:
	start(_start),
	end(_end)
{
}
