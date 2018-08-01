#pragma once
#include "Matrix3.h"

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
	Matrix4();
	Matrix4(float m00, float m01, float m02, float m03,
		float m10, float m11, float m12, float m13,
		float m20, float m21, float m22, float m23,
		float m30, float m31, float m32, float m33);

public:
	inline float* operator[](int index) { return &(data[index * 4]); }
	Matrix4& operator*(float scale);
public:
	Matrix4 Transpose() const;
	float Determinant() const;
	Matrix3 Cut(int row, int col) const;
	Matrix4 Minor() const;
	Matrix4 Cofactor() const;
	Matrix4 Adjugate() const;
	Matrix4 Invert() const;
};