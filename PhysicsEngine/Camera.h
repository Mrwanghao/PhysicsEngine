#pragma once
#include "Matrix4.h"


class Camera
{
protected:
	float fov;
	float aspect;
	float near;
	float far;
	float width;
	float height;

	Matrix4 worldMat;
	Matrix4 projectionMat;
	int cameraType;

public:
	Camera();
	virtual ~Camera();

	Matrix4 GetWorldMat();
	Matrix4 GetViewMat();
	Matrix4 GetProjMat();

	inline void SetProjMat(const Matrix4& _projMat) { projectionMat = _projMat; }
	inline void SetWorldMat(const Matrix4& _worldMat) { worldMat = _worldMat; }
	float GetAspect();
	bool IsOrthographic();
	bool IsPerspective();
	bool IsOrthoNormal();
	void OrthoNormalize();
	void Resize(int width, int height);
	void Perspective(float fov, float aspect,
		float zNear, float zFar);
	void Orthographic(float width, float height,
		float zNear, float zFar);

};