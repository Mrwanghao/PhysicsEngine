#pragma once


class Vec3
{
public:
	union
	{
		struct
		{
			float x;
			float y;
			float z;
		};
		float data[3];
	};

public:
	Vec3();
	Vec3(float _x, float _y, float _z);

};