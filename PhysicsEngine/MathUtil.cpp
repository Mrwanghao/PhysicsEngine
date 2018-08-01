#include "MathUtil.h"

Matrix4 Translation(float _x, float _y, float _z)
{
	return Matrix4(1.0f, 0.0f, 0.0f, 0.0f,
				   0.0f, 1.0f, 0.0f, 0.0f,
				   0.0f, 0.0f, 1.0f, 0.0f,
				   _x,     _y,   _z, 1.0f);
}

Vec3 GetTranslation(const Matrix4 & mat)
{
	return Vec3(mat.m30, mat.m31, mat.m32);
}

Matrix4 Scale(float _x, float _y, float _z)
{
	return Matrix4(_x, 0.0f, 0.0f, 0.0f,
				   0.0f, _y, 0.0f, 0.0f,
				   0.0f, 0.0f, _z, 0.0f,
				   0.0f, 0.0f, 0.0f, 1.0f);
}

Vec3 GetScale(const Matrix4 & mat)
{
	return Vec3(mat.m00, mat.m11, mat.m22);
}
