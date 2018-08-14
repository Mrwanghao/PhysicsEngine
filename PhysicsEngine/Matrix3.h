#pragma once
#include "Matrix2.h"


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
	Matrix3();
	Matrix3(float m00, float m01, float m02,
		float m10, float m11, float m12,
		float m20, float m21, float m22);

public:
	inline float* operator[](int index) { return &(data[index * 3]); }
	Matrix3& operator*(float scale);
	Matrix3 operator*(const Matrix3& right) const;
public:
	Matrix3 Transpose() const;
	float Determinant() const;
	Matrix2 Cut(int row, int col) const;
	Matrix3 Minor() const;
	Matrix3 Cofactor() const;
	Matrix3 Adjugate() const;
	Matrix3 Invert() const;
};