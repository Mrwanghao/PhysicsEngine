#pragma once


class Matrix2
{
public:
	union
	{
		struct
		{
			float m00, m01,
				m10, m11;
		};
		float data[4];
	};

public:
	inline float* operator[](int index) { return &(data[index * 2]); }

};
