#pragma once
class Matrix4
{
public:
	union
	{
		struct
		{
			float m00, m01, m02, m03,
				m10, m11, m12, m13,
				m20, m21, m22, m23,
				m30, m31, m32, m33;
		};
		float data[16];
	};

public:
	inline float* operator[](int index) { return &(data[index * 4]); }

};