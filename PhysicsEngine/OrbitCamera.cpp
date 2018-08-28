#include "OrbitCamera.h"
#include "Vec3.h"
#include "math3d.h"

float OrbitCamera::ClampAngle(float angle, float min, float max)
{
	while (angle < -360) {
		angle += 360;
	}
	while (angle > 360) {
		angle -= 360;
	}
	if (angle < min) {
		angle = min;
	}
	if (angle > max) {
		angle = max;
	}
	return angle;
}

OrbitCamera::OrbitCamera()
{
	target = Vec3(0, 0, 0);
	zoomDistance = 10.0f;
	zoomSpeed = 200.0f;
	rotationSpeed = Vec2(250.0f, 120.0f);
	yRotationLimit = Vec2(-20.0f, 80.0f);
	zoomDistanceLimit = Vec2(3.0f, 15.0f);
	currentRotation = Vec2(0, 0);
	panSpeed = Vec2(180.0f, 180.0f);
}

void OrbitCamera::Rotate(const Vec2 & deltaRot, float deltaTime)
{
	currentRotation.x += deltaRot.x * rotationSpeed.x * zoomDistance * deltaTime;
	currentRotation.y += deltaRot.y * rotationSpeed.y * zoomDistance * deltaTime;
	currentRotation.x = ClampAngle(currentRotation.x, -360, 360);
	currentRotation.y = ClampAngle(currentRotation.y, yRotationLimit.x, yRotationLimit.y);
}

void OrbitCamera::Zoom(float deltaZoom, float deltaTime)
{
	zoomDistance = zoomDistance + deltaZoom * zoomSpeed * deltaTime;
	
	if (zoomDistance < zoomDistanceLimit.x) {
		zoomDistance = zoomDistanceLimit.x;
	}
	if (zoomDistance > zoomDistanceLimit.y) {
		zoomDistance = zoomDistanceLimit.y;
	}
}

void OrbitCamera::Pan(const Vec2 & delataPan, float deltaTime)
{
	Vec3 right(worldMat.m00, worldMat.m10, worldMat.m20);

	float xPanMag = delataPan.x * panSpeed.x * deltaTime;
	target = target - (right * xPanMag);

	float yPanMag = delataPan.y * panSpeed.y * deltaTime;
	target = target + (Vec3(0, 1, 0) * yPanMag);
}

void OrbitCamera::Update(float dt)
{
	Vec3 rotation = Vec3(currentRotation.y, currentRotation.x, 0);
	Matrix3 orient = Rot3x3(rotation.x, rotation.y, rotation.z);
	Vec3 direction = MultiplyVector(Vec3(0.0, 0.0, -zoomDistance), orient);
	Vec3 position = direction + target;
	worldMat = LookAt(position, target, Vec3(0, 1, 0)).Invert();
}
