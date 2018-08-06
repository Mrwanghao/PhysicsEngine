#pragma once
#include "Circle2D.h"
#include "Rectangle2D.h"

class BoundingShape
{
public:
	unsigned int circleCount;
	Circle2D* circles;
	unsigned int rectCount;
	Rectangle2D* rects;

public:
	BoundingShape();
	~BoundingShape();

};