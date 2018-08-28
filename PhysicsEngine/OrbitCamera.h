#pragma once
#include "Camera.h"
#include "Vec2.h"



class OrbitCamera : public Camera
{
protected:
	Vec3 target;
	Vec2 panSpeed;
	float zoomDistance;
	Vec2 zoomDistanceLimit;
	float zoomSpeed;
	Vec2 rotationSpeed;
	Vec2 yRotationLimit; // x = min, y = max
	Vec2 currentRotation;

	float ClampAngle(float angle, float min, float max);
public:
	OrbitCamera();
	inline virtual ~OrbitCamera() { }
	void Rotate(const Vec2& deltaRot, float deltaTime);
	void Zoom(float deltaZoom, float deltaTime);
	void Pan(const Vec2& delataPan, float deltaTime);
	void Update(float dt);

};