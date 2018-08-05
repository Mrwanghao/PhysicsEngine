#pragma once
#include "Vec2.h"
#include "Line2D.h"
#include "Circle2D.h"
#include "Rectangle2D.h"
#include "OrientedRectangle2D.h"

class Interval2D
{
public:
	float min;
	float max;
};

Interval2D GetInterval(const Rectangle2D& rect, const Vec2& axis);
bool OverlapOnAxis(const Rectangle2D& rect1, const Rectangle2D& rect2, const Vec2& axis);
bool RectangleRectangleSAT(const Rectangle2D & rect1, const Rectangle2D & rect2);

Interval2D GetInterval(const OrientedRectangle2D& orientedRectangle, const Vec2& axis);
bool OverlapOnAxis(const Rectangle2D& rect, const OrientedRectangle2D& orientedRectangle, const Vec2& axis);
bool RectangleOrientedRectangle(const Rectangle2D& rect, const OrientedRectangle2D& orientedRectangle);

bool OrientedRectangleOrientedRectangle(const OrientedRectangle2D& orientedRectangle1, const OrientedRectangle2D& orientedRectangle2);

bool Point2DOnLine2D(const Point2D& _point, const Line2D& _line2d);
bool Point2DInCircle2D(const Point2D& _point, const Circle2D& _circle2d);
bool Point2DInRectangle2D(const Point2D& _point, const Rectangle2D& _rect2d);
bool Point2DInPrientedRectangle2D(const Point2D& _point, const OrientedRectangle2D& _orientedrect2d);

bool LineCircle(const Line2D& line, const Circle2D& circle);
bool LineRectangle(const Line2D& l, const Rectangle2D& r);
bool LineOrientedRectangle(const Line2D& line, const OrientedRectangle2D& rectangle);

bool CircleCircle(const Circle2D& c1, const Circle2D& c2);
bool CircleRectangle(const Circle2D& circle, const Rectangle2D& rectangle);
bool CircleOrientedRectangle(const Circle2D& circle, const OrientedRectangle2D& orientedRectangle);
bool RectangleRectangle(const Rectangle2D& rect1, const Rectangle2D& rect2);
bool RectangleToOrientedRectangle(const Rectangle2D& rect, const OrientedRectangle2D& orientedRectangle);
bool OrientedRectangleToOrientedRectangle(const OrientedRectangle2D& orientedRectangle1, const OrientedRectangle2D& orientedRectangle2);

