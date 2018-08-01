#pragma once


class Matrix3
{
public:
	union
	{
		struct
		{
			float m00, m01, m02,
				m10, m11, m12,
				m20, m21, m22;
		};
		float data[9];
	};

public:
	inline float* operator[](int index) { return &(data[index * 3]); }

};