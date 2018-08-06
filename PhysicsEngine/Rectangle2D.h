#pragma once
#include "Vec2.h"

class Rectangle2D
{
	Point2D origin;
	Vec2 size;

public:
	Rectangle2D();
	Rectangle2D(const Point2D& _origin, const Vec2& _size);

public:
	Vec2 GetMin() const;
	Vec2 GetMax() const;
	static Rectangle2D FromMinToMax(const Vec2& min, const Vec2& max);
};

