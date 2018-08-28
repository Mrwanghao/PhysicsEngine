#include "draw.h"
#include "MathUtil.h"




Matrix4 FromMat3(const Matrix3& mat) {
	Matrix4 result;

	result.m00 = mat.m00;
	result.m01 = mat.m01;
	result.m02 = mat.m02;

	result.m10 = mat.m10;
	result.m11 = mat.m11;
	result.m12 = mat.m12;

	result.m20 = mat.m20;
	result.m21 = mat.m21;
	result.m22 = mat.m22;

	result.m33 = 1.0f;

	return result;
}

void RenderOBB(const OBB& obb) {
	glPushMatrix();

	Matrix4 scale = Scale(obb.size.x, obb.size.y, obb.size.z);
	Matrix4 rotation = FromMat3(obb.orientation);
	Matrix4 translation = Translation(obb.origin.x, obb.origin.y, obb.origin.z);

	Matrix4 transform = scale * rotation * translation;

	glMultMatrixf(transform.data);
	FixedFunctionCube();
	glPopMatrix();
}

void FixedFunctionCube() {
	FixedFunctionCube(1.0f, 1.0f, 1.0f);
}

void FixedFunctionCube(float extentsX, float extentsY, float extentsZ) {
	float min[] = { -extentsX, -extentsY, -extentsZ };
	float max[] = { +extentsX, +extentsY, +extentsZ };

	glBegin(GL_TRIANGLES);
	glColor3f(0.5f, 0.5f, 1.0f);
#if 1
	glNormal3f(0.0f, 1.0f, 0.0f);
	glVertex3f(min[0], max[1], min[2]);
	glVertex3f(max[0], max[1], min[2]);
	glVertex3f(min[0], max[1], max[2]);
	glVertex3f(max[0], max[1], min[2]);
	glVertex3f(max[0], max[1], max[2]);
	glVertex3f(min[0], max[1], max[2]);
#endif

#if 1
	glNormal3f(0.0f, 0.0f, 1.0f);
	glVertex3f(min[0], max[1], max[2]);
	glVertex3f(max[0], max[1], max[2]);
	glVertex3f(min[0], min[1], max[2]);
	glVertex3f(max[0], max[1], max[2]);
	glVertex3f(max[0], min[1], max[2]);
	glVertex3f(min[0], min[1], max[2]);
#endif

#if 1
	glNormal3f(-1.0f, 0.0f, 0.0f);
	glVertex3f(min[0], max[1], max[2]);
	glVertex3f(min[0], min[1], max[2]);
	glVertex3f(min[0], max[1], min[2]);
	glVertex3f(min[0], max[1], min[2]);
	glVertex3f(min[0], min[1], max[2]);
	glVertex3f(min[0], min[1], min[2]);
#endif

#if 1
	glNormal3f(0.0f, -1.0f, 0.0f);
	glVertex3f(min[0], min[1], min[2]);
	glVertex3f(min[0], min[1], max[2]);
	glVertex3f(max[0], min[1], min[2]);
	glVertex3f(max[0], min[1], min[2]);
	glVertex3f(min[0], min[1], max[2]);
	glVertex3f(max[0], min[1], max[2]);
#endif

#if 1
	glNormal3f(0.0f, 0.0f, -1.0f);
	glVertex3f(min[0], max[1], min[2]);
	glVertex3f(min[0], min[1], min[2]);
	glVertex3f(max[0], max[1], min[2]);
	glVertex3f(max[0], max[1], min[2]);
	glVertex3f(min[0], min[1], min[2]);
	glVertex3f(max[0], min[1], min[2]);
#endif

#if 1
	glNormal3f(1.0f, 0.0f, 0.0f);
	glVertex3f(max[0], max[1], max[2]);
	glVertex3f(max[0], max[1], min[2]);
	glVertex3f(max[0], min[1], max[2]);
	glVertex3f(max[0], max[1], min[2]);
	glVertex3f(max[0], min[1], min[2]);
	glVertex3f(max[0], min[1], max[2]);
#endif

	glEnd();
}
















































