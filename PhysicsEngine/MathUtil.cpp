#include "MathUtil.h"
#include <math.h>

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

Matrix4 Projection(float fov, float near, float far, float aspect)
{
	Matrix4 projection;
	
	projection.m00 = 1 / (tan(fov * 0.5f) * aspect);
	projection.m11 = 1 / tan(fov * 0.5f);
	projection.m22 = far / (far - near);
	projection.m32 = (near * far) / (near - far);
	projection.m23 = 1.0f;
	return projection;
}

Matrix4 Ortho(float left, float right, float bottom, float top, float zNear, float zFar)
{
	float _11 = 2.0f / (right - left);
	float _22 = 2.0f / (top - bottom);
	float _33 = 1.0f / (zFar - zNear);
	float _41 = (left + right) / (left - right);
	float _42 = (top + bottom) / (bottom - top);
	float _43 = (zNear) / (zNear - zFar);
	
	return Matrix4(
		_11, 0.0f, 0.0f, 0.0f,
		0.0f, _22, 0.0f, 0.0f,
		0.0f, 0.0f, _33, 0.0f,
		_41, _42, _43, 1.0f
	);
}

Matrix4 Transform(const Vec3 & scale, const Vec3 & eulerRotation, const Vec3 & translate)
{
	return Scale(scale.x, scale.y, scale.z) *
		Rot(eulerRotation.x,
			eulerRotation.y,
			eulerRotation.z) *
		Translation(translate.x, translate.y, translate.z);
}

Matrix4 Transform(const Vec3 & scale, const Vec3 & rotationAxis, float rotationAngle, const Vec3 & translate)
{
	return Scale(scale.x, scale.y, scale.z) *
		AxisAngle(rotationAxis, rotationAngle) *
		Translation(translate.x, translate.y, translate.z);
}

Vec3 MultiplyPoint(const Vec3 & vec, const Matrix4 & mat)
{
	Vec3 result;
	result.x = vec.x * mat.m00 + vec.y * mat.m10 + vec.z * mat.m20 + 1.0f * mat.m30;
	result.y = vec.x * mat.m01 + vec.y * mat.m11 + vec.z * mat.m21 + 1.0f * mat.m31;
	result.z = vec.x * mat.m02 + vec.y * mat.m12 + vec.z * mat.m22 + 1.0f * mat.m32;
	return result;
}

Vec3 MultiplyVector(const Vec3 & vec, const Matrix4 & mat)
{
	Vec3 result;
	result.x = vec.x * mat.m00 + vec.y * mat.m10 + vec.z * mat.m20 + 1.0f * mat.m30;
	result.y = vec.x * mat.m01 + vec.y * mat.m11 + vec.z * mat.m21 + 1.0f * mat.m31;
	result.z = vec.x * mat.m02 + vec.y * mat.m12 + vec.z * mat.m22 + 1.0f * mat.m32;
	return result;
}

Vec3 MultiplyVector(const Vec3 & vec, const Matrix3 & mat)
{
	Vec3 result;
	result.x = vec.Dot(Vec3(mat.m00, mat.m01, mat.m02));
	result.y = vec.Dot(Vec3(mat.m10, mat.m11, mat.m12));
	result.z = vec.Dot(Vec3(mat.m20, mat.m21, mat.m22));
	return result;
}

Matrix4 LookAt(const Vec3 & position, const Vec3 & target, const Vec3 & up)
{
	Vec3 forward = (target - position).GetNormalized();
	Vec3 right = up.Cross(forward).GetNormalized();
	Vec3 newUp = forward.Cross(right);

	return Matrix4(
		right.x, right.y, right.z, 0.0f,
		newUp.x, newUp.y, newUp.z, 0.0f,
		forward.x, forward.y, forward.z, 0.0f,
		-right.Dot(position), -newUp.Dot(position), -forward.Dot(position), 1.0f
	);
}

Matrix4 Rot(float pitch, float yaw, float roll)
{
	return RotZ(roll) *
		RotX(pitch) *
		RotY(yaw);
}

Matrix3 Rot3x3(float pitch, float yaw, float roll)
{
	return RotZ3x3(yaw) *
		RotX3x3(pitch) *
		RotY3x3(yaw);
}

Matrix4 RotX(float angle)
{
	angle = DEG2RAD(angle);
	return Matrix4(
		1.0f, 0.0f, 0.0f, 0.0f,
		0.0f, cosf(angle), sinf(angle), 0.0f,
		0.0f, -sinf(angle), cos(angle), 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f
	);
}

Matrix4 RotY(float angle)
{
	angle = DEG2RAD(angle);
	return Matrix4(
		cosf(angle), 0.0f, -sinf(angle), 0.0f,
		0.0f, 1.0f, 0.0f, 0.0f,
		sinf(angle), 0.0f, cosf(angle), 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f
	);
}

Matrix4 RotZ(float angle)
{
	angle = DEG2RAD(angle);
	return Matrix4(
		cosf(angle), sinf(angle), 0.0f, 0.0f,
		-sinf(angle), cosf(angle), 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f
	);
}

Matrix3 RotX3x3(float angle)
{
	angle = DEG2RAD(angle);
	return Matrix3(
		1.0f, 0.0f, 0.0f,
		0.0f, cosf(angle), sinf(angle),
		0.0f, -sinf(angle), cos(angle)
	);
}

Matrix3 RotY3x3(float angle)
{
	angle = DEG2RAD(angle);
	return Matrix3(
		cosf(angle), 0.0f, -sinf(angle),
		0.0f, 1.0f, 0.0f,
		sinf(angle), 0.0f, cosf(angle)
	);
}

Matrix3 RotZ3x3(float angle)
{
	angle = DEG2RAD(angle);
	return Matrix3(
		cosf(angle), sinf(angle), 0.0f, 
		-sinf(angle), cosf(angle), 0.0f, 
		0.0f, 0.0f, 1.0f
	);
}

Matrix4 AxisAngle(const Vec3 & axis, float angle)
{
	angle = DEG2RAD(angle);
	float c = cosf(angle);
	float s = sinf(angle);
	float t = 1.0f - cosf(angle);
	float x = axis.x;
	float y = axis.y;
	float z = axis.z;
	if (!(axis.MagnitudeSq() == 1.0f)) {
		float inv_len = 1.0f / axis.Magnitude();
		x *= inv_len; // Normalize x
		y *= inv_len; // Normalize y
		z *= inv_len; // Normalize z
	} // x, y, and z are a normalized vector
	return Matrix4(
		t*(x*x) + c, t*x*y + s * z, t*x*z - s * y, 0.0f,
		t*x*y - s * z, t*(y*y) + c, t*y*z + s * x, 0.0f,
		t*x*z + s * y, t*y*z - s * x, t*(z*z) + c, 0.0f,
		0.0f, 0.0f, 0.0f, 1.0f
	);
}

Matrix3 AxisAngle3x3(const Vec3 & axis, float angle)
{
	angle = DEG2RAD(angle);
	float c = cosf(angle);
	float s = sinf(angle);
	float t = 1.0f - cosf(angle);
	
	float x = axis.x;
	float y = axis.y;
	float z = axis.z;
	if (!(axis.MagnitudeSq() == 1.0f)) {
		float inv_len = 1.0f / axis.Magnitude();
		x *= inv_len;
		y *= inv_len;
		z *= inv_len;
	}
	return Matrix3(
		t * (x * x) + c, t * x * y + s * z, t * x * z - s * y,
		t * x * y - s * z, t * (y * y) + c, t * y * z + s * x,
		t * x * z + s * y, t * y * z - s * x, t * (z * z) + c
	);
}



Matrix4 Projection(float fov, float aspect, float zNear, float zFar) {
	float tanHalfFov = tanf(DEG2RAD((fov * 0.5f)));
	float fovY = 1.0f / tanHalfFov; 
	float fovX = fovY / aspect; 
	Matrix4 result;
	result.m00 = fovX;
	result.m11 = fovY;
	result.m22 = zFar / (zFar - zNear);
	result.m23 = 1.0f;
	result.m32 = -zNear * result.m22;
	result.m33 = 0.0f;
	return result;
}