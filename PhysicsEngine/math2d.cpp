#include "math2d.h"
#include "MathUtil.h"
#include <math.h>
#include "Matrix2.h"

Interval2D GetInterval(const Rectangle2D & rect, const Vec2 & axis)
{
	Interval2D result;
	Vec2 min = rect.GetMin();
	Vec2 max = rect.GetMax();

	Vec2 verts[] =
	{
		Vec2(min.x, min.y), Vec2(min.x, max.y),
		Vec2(max.x, max.y), Vec2(max.x, min.y)
	};

	result.min = result.max = axis.Dot(verts[0]);

	for (int i = 1; i < 4; i++)
	{
		float projection = axis.Dot(verts[i]);

		if (projection < result.min)
		{
			result.min = projection;
		}

		if (projection > result.max)
		{
			result.max = projection;
		}

	}

	return result;
}

bool OverlapOnAxis(const Rectangle2D & rect1, const Rectangle2D & rect2, const Vec2 & axis)
{
	Interval2D a = GetInterval(rect1, axis);
	Interval2D b = GetInterval(rect2, axis);
	return b.min <= a.max && a.min <= b.max;
}

bool RectangleRectangleSAT(const Rectangle2D & rect1, const Rectangle2D & rect2)
{
	Vec2 axisToTest[] = { Vec2(1, 0), Vec2(0, 1) };

	for (int i = 0; i < 2; i++)
	{
		if (!OverlapOnAxis(rect1, rect2, axisToTest[i]))
		{
			return false;
		}
	}

	return true;
}

bool Point2DOnLine2D(const Point2D & _point, const Line2D & _line2d)
{
	Vec2 offset = _line2d.end - _line2d.start;
	if (offset.y == 0.0f)
	{
		return _point.x == _line2d.start.x;
	}

	if (offset.x == 0.0f)
	{
		return _point.y == _line2d.start.y;
	}

	float dy = (_line2d.end.y - _line2d.start.y);
	float dx = (_line2d.end.x - _line2d.start.x);
	float M = dy / dx;

	float B = _line2d.start.y - M * _line2d.start.x;

	return _point.y == M * _point.x + B;
}

bool Point2DInCircle2D(const Point2D & _point, const Circle2D & _circle2d)
{
	Line2D line(_point, _circle2d.center);
	if (line.LengthSq() < _circle2d.radius * _circle2d.radius)
	{
		return true;
	}

	return false;
}

bool Point2DInRectangle2D(const Point2D & _point, const Rectangle2D & _rect2d)
{
	Vec2 min = _rect2d.GetMin();
	Vec2 max = _rect2d.GetMax();

	return _point.x >= min.x && _point.x <= max.x && _point.y >= min.y && _point.y <= max.y;
}

bool Point2DInPrientedRectangle2D(const Point2D & _point, const OrientedRectangle2D & _orientedrect2d)
{
	Vec2 rotVector = _point - _orientedrect2d.origin;
	float theta = -DEG2RAD(_orientedrect2d.rotation);
	Matrix2 rotMatrix(cosf(theta), sinf(theta), -sinf(theta), cosf(theta));
	rotVector = rotVector * rotMatrix;

	Rectangle2D localRectangle2D(Point2D(), _orientedrect2d.halfExtents * 2);
	Vec2 localPoint = rotVector + _orientedrect2d.halfExtents;

	return Point2DInRectangle2D(localPoint, localRectangle2D);
}

bool LineCircle(const Line2D & line, const Circle2D & circle)
{
	Vec2 ab = line.end - line.start;
	float t = (circle.center - line.start).Dot(ab) / ab.Dot(ab);
	if (t < 0.0f || t > 1.0f) {
		return false;
	}
	Point2D closestPoint = line.start + ab * t;
	Line2D circleToClosest(circle.center, closestPoint);
	return circleToClosest.LengthSq() < circle.radius * circle.radius;
}

bool LineRectangle(const Line2D & l, const Rectangle2D & r)
{
	if (Point2DInRectangle2D(l.start, r) || Point2DInRectangle2D(l.end, r)) {
		return true;
	}
	Vec2 norm = (l.end - l.start).GetNormalized();
	norm.x = (norm.x != 0) ? 1.0f / norm.x : 0;

	norm.y = (norm.y != 0) ? 1.0f / norm.y : 0;
	Vec2 min = (r.GetMin() - l.start) * norm;
	Vec2 max = (r.GetMax() - l.start) * norm;
	float tmin = fmaxf(
		fminf(min.x, max.x),
		fminf(min.y, max.y)
	);
	float tmax = fminf(
		fmaxf(min.x, max.x),
		fmaxf(min.y, max.y)
	);
	if (tmax< 0 || tmin>tmax) {
		return false;
	}
	float t = (tmin< 0.0f) ? tmax : tmin;
	return t > 0.0f && t * t < l.LengthSq();
}

bool LineOrientedRectangle(const Line2D & line, const OrientedRectangle2D & rectangle)
{
	float theta = -DEG2RAD(rectangle.rotation);
	Matrix2 rotMatrix(cosf(theta), sinf(theta), -sinf(theta), cosf(theta));
	Line2D localLine;

	Vec2 rotVector = line.start - rectangle.origin;
	rotVector = rotVector * rotMatrix;
	localLine.start = rotVector + rectangle.halfExtents;

	rotVector = line.end - rectangle.origin;
	rotVector = rotVector * rotMatrix;
	localLine.end = rotVector + rectangle.halfExtents;

	Rectangle2D localRectangle(Point2D(), rectangle.halfExtents * 2.0f);
	return LineRectangle(localLine, localRectangle);
}

bool CircleCircle(const Circle2D & c1, const Circle2D & c2)
{
	Line2D line(c1.center, c2.center);
	float radiusSum = c1.radius + c2.radius;
	return line.LengthSq() <= radiusSum;
}

bool CircleRectangle(const Circle2D & circle, const Rectangle2D & rectangle)
{
	Vec2 min = rectangle.GetMin();
	Vec2 max = rectangle.GetMax();

	Point2D closestPoint = circle.center;

	closestPoint.x = closestPoint.x < min.x ? min.x : closestPoint.x;
	closestPoint.x = closestPoint.x > max.x ? max.x : closestPoint.x;

	closestPoint.y = closestPoint.y < min.y ? min.y : closestPoint.y;
	closestPoint.y = closestPoint.y > max.y ? max.y : closestPoint.y;

	Line2D line(circle.center, closestPoint);

	return line.LengthSq() <= circle.radius * circle.radius;
}

bool CircleOrientedRectangle(const Circle2D & circle, const OrientedRectangle2D & orientedRectangle)
{
	Vec2 r = circle.center - orientedRectangle.origin;

	float theta = -DEG2RAD(orientedRectangle.rotation);
	Matrix2 zRotation(cosf(theta), sinf(theta), -sinf(theta), cos(theta));

	r = r * zRotation;

	Circle2D localCircle(r + orientedRectangle.halfExtents, circle.radius);
	Rectangle2D localRectangle(Point2D(), orientedRectangle.halfExtents * 2);

	return CircleRectangle(localCircle, localRectangle);
}

bool RectangleRectangle(const Rectangle2D & rect1, const Rectangle2D & rect2)
{
	Vec2 aMin = rect1.GetMin();
	Vec2 aMax = rect1.GetMax();
	Vec2 bMin = rect2.GetMin();
	Vec2 bMax = rect2.GetMax();

	bool overX = (bMin.x <= aMax.x && aMin.x <= bMax.x);
	bool overY = (bMin.y <= aMax.y && aMin.y <= bMax.y);

	return overX && overY;
}

bool RectangleToOrientedRectangle(const Rectangle2D & rect, const OrientedRectangle2D & orientedRectangle)
{
	return false;
}

bool OrientedRectangleToOrientedRectangle(const OrientedRectangle2D & orientedRectangle1, const OrientedRectangle2D & orientedRectangle2)
{
	return false;
}
