#pragma once
#include "glad/glad.h"
#include "Matrix4.h"
#include "OBB.h"


void FixedFunctionCube();
void FixedFunctionCube(float extentsX, float extentsY, float extentsZ);
void RenderOBB(const OBB& obb);
Matrix4 FromMat3(const Matrix3& mat);












