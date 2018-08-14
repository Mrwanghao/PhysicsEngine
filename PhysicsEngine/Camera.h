#pragma once
#include "Matrix4.h"
#include "Plane.h"

class Frustum {
public:
	union {
		struct {
			Plane top;
			Plane bottom;
			Plane left;
			Plane right;
			Plane _near;
			Plane _far;
		};
		Plane planes[6];
	};

	Frustum() { }
	~Frustum() {}
};

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
	inline Matrix4 GetProjMat() { return projectionMat; }

	inline void SetProjMat(const Matrix4& _projMat) { projectionMat = _projMat; }
	inline void SetWorldMat(const Matrix4& _worldMat) { worldMat = _worldMat; }
	inline float GetAspect() { return aspect; }
	bool IsOrthographic() { return cameraType == 1; }
	bool IsPerspective() { return cameraType == 0; }
	bool IsOrthoNormal();
	void OrthoNormalize();
	void Resize(int width, int height);
	void Perspective(float fov, float aspect,
		float zNear, float zFar);
	void Orthographic(float width, float height,
		float zNear, float zFar);

	void SetProjection(const Matrix4& projection);
	void SetWorld(const Matrix4& view);

	Frustum GetFrustum();

};

Camera CreatePerspective(float fieldOfView, float aspectRatio, float nearPlane, float farPlane);
Camera CreateOrthographic(float width, float height, float nearPlane, float farPlane);
