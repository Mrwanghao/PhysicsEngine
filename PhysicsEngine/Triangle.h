#pragma once
#include "Vec3.h"

class Triangle
{
public:
	union
	{
		float data[9];
		Vec3 points[3];
		struct 
		{
			Point3D a;
			Point3D b;
			Point3D c;
		};
	};

public:
	Triangle();
	Triangle(const Point3D& p1, const Point3D& p2, const Point3D& p3);
	~Triangle();
};

