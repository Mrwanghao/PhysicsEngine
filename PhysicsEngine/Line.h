#pragma once

#include "Vec3.h"


class Line
{
public:
	Point3D start;
	Point3D end;

public:
	Line();
	Line(const Point3D& _start, const Point3D& _end);

};