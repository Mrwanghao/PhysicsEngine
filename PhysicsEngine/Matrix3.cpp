#include "Matrix3.h"
#include <cmath>

Matrix3::Matrix3()
{
	for (int i = 0; i < 9; i++)
	{
		data[i] = 0.0f;
	}
}

Matrix3::Matrix3(float _m00, float _m01, float _m02, float _m10, float _m11, float _m12, float _m20, float _m21, float _m22)
{
	m00 = _m00;
	m01 = _m01;
	m02 = _m02;
	m10 = _m10;
	m11 = _m11;
	m12 = _m12;
	m20 = _m20;
	m21 = _m21;
	m22 = _m22;
}

Matrix3 & Matrix3::operator*(float scale)
{
	Matrix3 result;
	for (int i = 0; i < 9; i++)
	{
		result.data[i] = data[i] * scale;
	}
	return result;
}

Matrix3 Matrix3::operator*(const Matrix3 & right) const
{
	Matrix3 result;
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			float temp = 0.0f;
			for (int index = 0; index < 3; index++)
			{
				temp += data[i * 3 + index] * right.data[index * 3 + j];
			}
			result.data[i * 3 + j] = temp;
		}
	}
	return result;
}

Matrix3 Matrix3::Transpose() const
{
	Matrix3 result;
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			result.data[j * 3 + i] = data[i * 3 + j];
		}

	}
	return result;
}

float Matrix3::Determinant() const
{
	float result = 0.0f;
	Matrix3 cofactor = Cofactor();
	for (int j = 0; j < 3; j++)
	{
		int index = 3 * 0 + j;
		result += data[index] * cofactor.data[0 * 3 + j];
	}

	return result;
}

Matrix2 Matrix3::Cut(int row, int col) const
{
	Matrix2 result;
	int index = 0;
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			if (i == row || j == col)
			{
				continue;
			}
			
			int dest = index++;
			int source = i * 3 + j;

			result.data[dest] = data[source];

		}
	}

	return result;
}

Matrix3 Matrix3::Minor() const
{
	Matrix3 result;
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			result.data[i * 3 + j] = Cut(i, j).Determinant();
		}
	}
	return result;
}

Matrix3 Matrix3::Cofactor() const
{
	Matrix3 result;
	Matrix3 minor = Minor();
	for (int i = 0; i < 3; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			result.data[i * 3 + j] = minor.data[i * 3 + j] * pow(-1.0f, i + j);
		}
	}
	return result;
}

Matrix3 Matrix3::Adjugate() const
{
	return Cofactor().Transpose();
}

Matrix3 Matrix3::Invert() const
{
	float det = Determinant();
	if (det == 0) return Matrix3();
	return Adjugate() * (1.0f / det);
}
