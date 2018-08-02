#pragma once

#include "Matrix4.h"
#include "Vec3.h"

#define RAD2DEG(x) ((x) * 57.295754f)
#define DEG2RAD(x) ((x) * 0.0174533f)


Matrix4 Translation(float _x, float _y, float _z);
Vec3 GetTranslation(const Matrix4& mat);

Matrix4 Scale(float _x, float _y, float _z);
Vec3 GetScale(const Matrix4& mat);

