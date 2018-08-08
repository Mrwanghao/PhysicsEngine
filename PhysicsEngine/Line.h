#pragma once

#include "Vec3.h"
#include "MathUtil.h"

class Line
{
public:
	Point3D start;
	Point3D end;

public:
	Line();
	Line(const Point3D& _start, const Point3D& _end);

	inline float Getlength() const { return (end - start).Magnitude(); }
	inline float GetLengthSq() const { return (end - start).MagnitudeSq(); }

};