#pragma once

#include "Vec3.h"
#include "Matrix4.h"

#define RAD2DEG(x) ((x) * 57.295754f)
#define DEG2RAD(x) ((x) * 0.0174533f)

#define FMINF(a, b) ((a) <= (b) ? (a) : (b))
#define FMAXF(a, b) ((a) >= (b) ? (a) : (b))

Matrix4 Translation(float _x, float _y, float _z);
Vec3 GetTranslation(const Matrix4& mat);

Matrix4 Scale(float _x, float _y, float _z);
Vec3 GetScale(const Matrix4& mat);

Matrix4 Projection(float fov, float near, float far, float aspect);
Matrix4 Ortho(float left, float right, float bottom, float top, float zNear, float zFar);

Matrix4 LookAt(const Vec3& position, const Vec3& target, const Vec3& up);

Matrix4 Rot(float pitch, float yaw, float roll);
Matrix3 Rot3x3(float pitch, float yaw, float roll);
Matrix4 RotX(float angle);
Matrix4 RotY(float angle);
Matrix4 RotZ(float angle);
Matrix3 RotX3x3(float angle);
Matrix3 RotY3x3(float angle);
Matrix3 RotZ3x3(float angle);

Matrix4 AxisAngle(const Vec3& axis, float angle);
Matrix3 AxisAngle3x3(const Vec3& axis, float angle);

Matrix4 Projection(float fov, float aspect, float zNear, float zFar);

Matrix4 Transform(const Vec3& scale, const Vec3& eulerRotation, const Vec3& translate);
Matrix4 Transform(const Vec3& scale, const Vec3& rotationAxis, float rotationAngle, const Vec3& translate);

Vec3 MultiplyPoint(const Vec3& vec, const Matrix4& mat);
Vec3 MultiplyVector(const Vec3& vec, const Matrix4& mat);
Vec3 MultiplyVector(const Vec3& vec, const Matrix3& mat);
