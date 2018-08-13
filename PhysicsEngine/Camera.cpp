#include "Camera.h"

#include "MathUtil.h"


Camera::Camera()
{
	fov = 60.0f;
	aspect = 1.3f;
	near = 0.01f;
	far = 1000.0f;
	width = 1.0;
	height = 1.0f;

	worldMat = Matrix4();
	projectionMat = Projection(fov, near, far, aspect);
	cameraType = 0;
}

Camera::~Camera()
{

}

