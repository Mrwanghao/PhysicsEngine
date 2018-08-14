#include "Camera.h"

#include "MathUtil.h"

//初始化相机参数 但是基本无用
Camera::Camera()
{
	fov = 60.0f;
	aspect = 1.3f;
	near = 0.01f;
	far = 1000.0f;
	width = 1.0;
	height = 1.0f;

	worldMat = Matrix4();
	
	projectionMat = Projection(fov, aspect, near, far);
	cameraType = 0;
}

Camera::~Camera()
{
}

Matrix4 Camera::GetWorldMat()
{
	return worldMat;
}

//计算相机矩阵
Matrix4 Camera::GetViewMat()
{
	if (!IsOrthoNormal())
		OrthoNormalize();

	Matrix4 inverse = worldMat.Transpose();
	inverse.m30 = inverse.m03 = 0.0f;
	inverse.m31 = inverse.m13 = 0.0f;
	inverse.m32 = inverse.m23 = 0.0f;

	Vec3 right = Vec3(worldMat.m00, worldMat.m01, worldMat.m02);
	Vec3 up = Vec3(worldMat.m10, worldMat.m11, worldMat.m12);
	Vec3 forward = Vec3(worldMat.m20, worldMat.m21, worldMat.m22);
	Vec3 position = Vec3(worldMat.m30, worldMat.m31, worldMat.m32);

	inverse.m30 = -right.Dot(position);
	inverse.m31 = -up.Dot(position);
	inverse.m32 = -forward.Dot(position);

	return inverse;

}

//判断当前的矩阵是否是归一化的
bool Camera::IsOrthoNormal()
{
	Vec3 right = Vec3(worldMat.m00, worldMat.m01, worldMat.m02);
	Vec3 up =    Vec3(worldMat.m10, worldMat.m11, worldMat.m12);
	Vec3 forward = Vec3(worldMat.m20, worldMat.m21, worldMat.m22);
	
	if (!(right.Dot(right) == 1.0f) || !(up.Dot(up) == 1.0f) || !(forward.Dot(forward) == 1.0f)) 
	{
		return false; 
	}

	if (!(forward.Dot(up) == 0.0f) || !(forward.Dot(right) == 0.0f) || !(right.Dot(up) == 0.0f)) 
	{
		return false;
	}
	return true;
}

//将每个轴向归一化
void Camera::OrthoNormalize()
{
	//得到相机坐标系下的三个轴向
	Vec3 right = Vec3(worldMat.m00, worldMat.m01, worldMat.m02);
	Vec3 up = Vec3(worldMat.m10, worldMat.m11, worldMat.m12);
	Vec3 forward = Vec3(worldMat.m20, worldMat.m21, worldMat.m22);

	Vec3 f = forward.GetNormalized();
	Vec3 r = up.Cross(f).GetNormalized();
	Vec3 u = f.Cross(r);

	worldMat = Matrix4(
		r.x, r.y, r.z, 0.0f,
		u.x, u.y, u.z, 0.0f,
		f.x, f.y, f.z, 0.0f,
		worldMat.m30, worldMat.m31, worldMat.m32, 1.0f
	);
}

//重新设置宽高
void Camera::Resize(int width, int height)
{
	aspect = (float)width / (float)height;

	if (cameraType == 0) { // Perspective
		projectionMat = Projection(fov, aspect, near, far);
	}
	else if (cameraType == 1) { // Ortho
		width = (float)width;
		height = (float)height;

		float halfW = width * 0.5f;
		float halfH = height * 0.5f;

		projectionMat = Ortho(-halfW, halfW, halfH, -halfH, near, far);
	}
}

//产生一个透视投影矩阵
void Camera::Perspective(float fov, float aspect, float zNear, float zFar)
{
	fov = fov;
	aspect = aspect;
	near = zNear;
	far = zFar;

	projectionMat = Projection(fov, aspect, zNear, zFar);
	cameraType = 0;
}

//产生一个正交投影矩阵
void Camera::Orthographic(float width, float height, float zNear, float zFar)
{
	width = width;
	height = height;
	near = zNear;
	far = zFar;

	float halfW = width * 0.5f;
	float halfH = height * 0.5f;

	projectionMat = Ortho(-halfW, halfW, halfH, -halfH, zNear, zFar);
	cameraType = 1;
}

//透视投影矩阵也是外界设置的
void Camera::SetProjection(const Matrix4 & projection)
{
	projectionMat = projection;
	cameraType = 2;
}

//摄像机矩阵是通过外界设置的
void Camera::SetWorld(const Matrix4 & view)
{
	worldMat = view;
}

Frustum Camera::GetFrustum()
{
	Frustum result;

	Matrix4 vp = GetViewMat() * GetProjMat();

	Vec3 col1(vp.m00, vp.m10, vp.m20);//, vp._41 };
	Vec3 col2(vp.m01, vp.m11, vp.m21);//, vp._42 };
	Vec3 col3(vp.m02, vp.m12, vp.m22);//, vp._43 };
	Vec3 col4(vp.m03, vp.m13, vp.m23);//, vp._44 };

									  // Find plane magnitudes
	result.left.normal = col4 + col1;
	result.right.normal = col4 - col1;
	result.bottom.normal = col4 + col2;
	result.top.normal = col4 - col2;
	result._near.normal = /*col4 +*/ col3;
	result._far.normal = col4 - col3;

	// Find plane distances
	result.left.distance = vp.m33 + vp.m30;
	result.right.distance = vp.m33 - vp.m30;
	result.bottom.distance = vp.m33 + vp.m31;
	result.top.distance = vp.m33 - vp.m31;
	result._near.distance = /*vp._44 +*/ vp.m32;
	result._far.distance = vp.m33 - vp.m32;

	// Normalize all 6 planes
	for (int i = 0; i < 6; ++i) {
		float mag = 1.0f / result.planes[i].normal.Magnitude();
		result.planes[i].normal.Normalize();
		result.planes[i].distance *= mag;
	}

	return result;
}
//根据参数返回一个透视摄像机
Camera CreatePerspective(float fieldOfView, float aspectRatio, float nearPlane, float farPlane)
{
	Camera result;
	result.Perspective(fieldOfView, aspectRatio, nearPlane, farPlane);
	return result;
}

//根据参数返回一个正交摄像机
Camera CreateOrthographic(float width, float height, float nearPlane, float farPlane)
{
	Camera result;
	result.Orthographic(width, height, nearPlane, farPlane);
	return result;
}
