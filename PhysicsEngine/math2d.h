#pragma once
#include "Vec2.h"
#include "Line2D.h"
#include "Circle2D.h"
#include "Rectangle2D.h"
#include "OrientedRectangle2D.h"

bool Point2DOnLine2D(const Point2D& _point, const Line2D& _line2d);
bool Point2DInCircle2D(const Point2D& _point, const Circle2D& _circle2d);
bool Point2DInRectangle2D(const Point2D& _point, const Rectangle2D& _rect2d);
bool Point2DInPrientedRectangle2D(const Point2D& _point, const OrientedRectangle2D& _orientedrect2d);

bool LineCircle(const Line2D& line, const Circle2D& circle);
bool LineRectangle(const Line2D& l, const Rectangle2D& r);
bool LineOrientedRectangle(const Line2D& line,
	const OrientedRectangle2D& rectangle);
