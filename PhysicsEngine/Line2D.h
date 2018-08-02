#pragma once
#include "Vec2.h"

class Line2D
{
public:
	Point2D start;
	Point2D end;

public:
	Line2D();
	Line2D(const Point2D& _start, const Point2D& _end);

public:
	float Length() const;
	float LengthSq() const;
};