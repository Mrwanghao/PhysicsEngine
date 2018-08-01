#include "Matrix2.h"
#include <cmath>

Matrix2::Matrix2()
{
	for (int i = 0; i < 4; i++)
	{
		data[i] = 0.0f;
	}
}

Matrix2::Matrix2(float _m00, float _m01, float _m10, float _m11)
{
	m00 = _m00;
	m01 = _m01;
	m10 = _m10;
	m11 = _m11;
}

Matrix2& Matrix2::operator*(float scale)
{
	Matrix2 result;
	for (int i = 0; i < 4; i++)
	{
		result.data[i] = data[i] * scale;
	}
	return result;
}

Matrix2 Matrix2::Transpose() const
{
	Matrix2 result;
	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 2; j++)
		{
			result.data[j * 2 + i] = data[i * 2 + j];
		}

	}
	return result;
}

float Matrix2::Determinant() const
{
	return m00 * m11 - m01 * m10;
}

Matrix2 Matrix2::Minor() const
{
	return Matrix2(m11, m10, m01, m00);
}

Matrix2 Matrix2::Cofactor() const
{
	Matrix2 result;
	Matrix2 minor = Minor();
	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 2; j++)
		{
			result.data[i * 2 + j] = minor.data[i * 2 + j] * pow(-1.0f, i + j);
		}
	
	}
	return result;
}

Matrix2 Matrix2::Adjugate() const
{
	return Cofactor().Transpose();
}

Matrix2 Matrix2::Invert() const
{
	float det = Determinant();
	if (det == 0) return Matrix2();
	return Adjugate() * (1.0f / det);
}
