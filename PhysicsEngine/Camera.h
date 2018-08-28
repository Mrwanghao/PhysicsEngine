#pragma once
#include "Matrix4.h"
#include "Plane.h"
#include "Frustum.h"


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

	inline Matrix4 GetWorldMat() { return worldMat; }
	Matrix4 GetViewMat();//就是摄像机的世界矩阵的逆矩阵
	inline Matrix4 GetProjMat() { return projectionMat; }

	void SetProjection(const Matrix4& projection);
	void SetWorld(const Matrix4& view);

	inline float GetAspect() { return aspect; }
	inline bool IsOrthographic() { return cameraType == 1; }
	inline bool IsPerspective() { return cameraType == 0; }

	bool IsOrthoNormal();
	void OrthoNormalize();
	void Resize(int width, int height);
	void Perspective(float fov, float aspect,
		float zNear, float zFar);
	void Orthographic(float width, float height,
		float zNear, float zFar);

	

	Frustum GetFrustum();

};

Camera CreatePerspective(float fieldOfView, float aspectRatio, float nearPlane, float farPlane);
Camera CreateOrthographic(float width, float height, float nearPlane, float farPlane);


