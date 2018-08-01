#include "Matrix4.h"
#include <cmath>
Matrix4::Matrix4()
{
	for (int i = 0; i < 16; i++)
	{
		data[i] = 0.0f;
	}
}

Matrix4::Matrix4(float _m00, float _m01, float _m02, float _m03, float _m10, float _m11, float _m12, float _m13, float _m20, float _m21, float _m22, float _m23, float _m30, float _m31, float _m32, float _m33)
{
	m00 = _m00;
	m01 = _m01;
	m02 = _m02;
	m03 = _m03;
	m10 = _m10;
	m11 = _m11;
	m12 = _m12;
	m13 = _m13;
	m20 = _m20;
	m21 = _m21;
	m22 = _m22;
	m23 = _m23;
	m30 = _m30;
	m31 = _m31;
	m32 = _m32;
	m33 = _m33;
}

Matrix4 & Matrix4::operator*(float scale)
{
	Matrix4 result;
	for (int i = 0; i < 16; i++)
	{
		result.data[i] = data[i] * scale;
	}
	return result;
}

Matrix4 Matrix4::Transpose() const
{
	Matrix4 result;
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			result.data[j * 4 + i] = data[i * 4 + j];
		}

	}
	return result;
}

float Matrix4::Determinant() const
{
	float result = 0.0f;
	Matrix4 cofactor = Cofactor();
	for (int j = 0; j < 4; j++)
	{
		int index = 4 * 0 + j;
		result += data[index] * cofactor.data[0 * 4 + j];
	}

	return result;
}

Matrix3 Matrix4::Cut(int row, int col) const
{
	Matrix3 result;
	int index = 0;
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			if (i == row || j == col)
			{
				continue;
			}

			int dest = index++;
			int source = i * 4 + j;

			result.data[dest] = data[source];

		}
	}

	return result;
}

Matrix4 Matrix4::Minor() const
{
	Matrix4 result;
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			result.data[i * 4 + j] = Cut(i, j).Determinant();
		}
	}
	return result;
}

Matrix4 Matrix4::Cofactor() const
{
	Matrix4 result;
	Matrix4 minor = Minor();
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			result.data[i * 4 + j] = minor.data[i * 4 + j] * pow(-1.0f, i + j);
		}
	}
	return result;
}

Matrix4 Matrix4::Adjugate() const
{
	return Cofactor().Transpose();
}

Matrix4 Matrix4::Invert() const
{
	float det = Determinant();
	if (det == 0) return Matrix4();
	return Adjugate() * (1.0f / det);
}
