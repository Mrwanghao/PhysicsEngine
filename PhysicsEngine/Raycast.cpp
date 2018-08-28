#include "Raycast.h"
#include <math.h>
#include "math3d.h"

bool Raycast(const Sphere & sphere, const Ray & ray, RaycastResult & result)
{
	result.Reset();

	Vec3 e = sphere.center - ray.origin;
	float rsq = sphere.radius * sphere.radius;
	float esq = e.MagnitudeSq();
	float a = e.Dot(ray.direction);
	float bsq = esq - a * a;
	float f = sqrtf(rsq - bsq);

	float t = a - f;

	if (rsq - (esq - a * a) < 0.0f) 
	{
		return false;
	}
	else if (esq < rsq) 
	{ 
		t = a + f; 
	}
	
	result.t = t;
	result.hit = true;
	result.point = ray.origin + ray.direction * t;
	result.normal = (result.point - sphere.center).GetNormalized();
	
	return true;
}


bool Raycast(const Plane & plane, const Ray & ray, RaycastResult & result)
{
	result.Reset();
	
	float nd = ray.direction.Dot(plane.normal);
	float pn = ray.origin.Dot(plane.normal);
	
	if (nd >= 0.0f) { return false; }
	
	float t = (plane.distance - pn) / nd;
	
	if (t >= 0.0f) { 
		result.t = t;
		result.hit = true;
		result.point = ray.origin + ray.direction*t;
		result.normal = plane.normal.GetNormalized();
			
		return true;
	}
	return false;
}



bool Raycast(const AABB & aabb, const Ray & ray, RaycastResult & result)
{
	Vec3 min = aabb.GetMin();
	Vec3 max = aabb.GetMax();

	float t[] = {0, 0, 0, 0, 0, 0};
	
	t[0] = (min.x - ray.origin.x) / (ray.direction.x == 0.0f ? 0.0000001f : ray.direction.x);
	t[1] = (max.x - ray.origin.x) / (ray.direction.x == 0.0f ? 0.0000001f : ray.direction.x);
	t[2] = (min.y - ray.origin.y) / (ray.direction.y == 0.0f ? 0.0000001f : ray.direction.y);
	t[3] = (max.y - ray.origin.y) / (ray.direction.y == 0.0f ? 0.0000001f : ray.direction.y);
	t[4] = (min.z - ray.origin.z) / (ray.direction.z == 0.0f ? 0.0000001f : ray.direction.z);
	t[5] = (max.z - ray.origin.z) / (ray.direction.z == 0.0f ? 0.0000001f : ray.direction.z);

	float tmin = fmaxf(fmaxf(fminf(t[0], t[1]), fminf(t[2], t[3])), fminf(t[4], t[5]));
	float tmax = fminf(fminf(fmaxf(t[0], t[1]), fmaxf(t[2], t[3])), fmaxf(t[4], t[5]));

	if (tmax < 0.0f)
	{
		return false;
	}

	if (tmax < tmin)
	{
		return false;
	}

	float t_result = tmin;

	if (tmin < 0.0f)
	{
		t_result = tmax;
	}

	result.t = t_result;
	result.hit = true;
	result.point = ray.origin + ray.direction * t_result;

	//六个面的法线
	Vec3 normals[] =
	{
		Vec3(-1.0f,  0.0f,  0.0f),
		Vec3( 1.0f,  0.0f,  0.0f),
		Vec3( 0.0f, -1.0f,  0.0f),
		Vec3( 0.0f,  1.0f,  0.0f),
		Vec3( 0.0f,  0.0f, -1.0f),
		Vec3( 0.0f,  0.0f,  1.0f),
	};

	//找到自己的那个法线
	for (int i = 0; i < 6; i++)
	{
		if (compare(t_result, t[i]))
		{
			result.normal = normals[i];
		}
	}

	return true;
}

bool Raycast(const OBB & obb, const Ray & ray, RaycastResult & result)
{
	const float* oriented = obb.orientation.data;
	 
	Vec3 p = ray.origin - obb.origin;

	//行向量
	Vec3 X(oriented[0], oriented[1], oriented[2]);
	Vec3 Y(oriented[3], oriented[4], oriented[5]);
	Vec3 Z(oriented[6], oriented[7], oriented[8]);

	//将射线方向转变到obb局部坐标系下
	Vec3 f = Vec3(X.Dot(ray.direction), Y.Dot(ray.direction), Z.Dot(ray.direction));

	//将起点转变到obb局部坐标系下
	Vec3 e(X.Dot(p), Y.Dot(p), Z.Dot(p));

	float t[6] = { 0, 0, 0, 0, 0, 0 };
	for (int i = 0; i < 3; ++i) {
		if (f[i] == 0) {
			//  左边界大于他的起点     ||  右边界 小于 它的起点
			if (-e[i] - obb.size.data[i] > 0 || -e[i] + obb.size.data[i] < 0) {
				return false;
			}
			//仍然需要初始化一个极小值
			f.data[i] = 0.0000001f; 
		}
		t[i * 2 + 0] = (e[i] + obb.size.data[i]) / f[i];
		t[i * 2 + 1] = (e[i] - obb.size.data[i]) / f[i];
	}
	
	//和aabb一样
	float tmin = fmaxf(
		fmaxf(
			fminf(t[0], t[1]),
			fminf(t[2], t[3])
		),
		fminf(t[4], t[5]));
	
	float tmax = fminf(
		fminf(
			fmaxf(t[0], t[1]),
			fmaxf(t[2], t[3])
		),
		fmaxf(t[4], t[5]));
	
	if (tmax < 0) { return false; }
	
	if (tmin > tmax) { return false; }
	
	float t_result = tmin;
	if (tmin < 0.0f) { t_result = tmax; }
	
	result.hit = true;
	result.t = t_result;
	result.point = ray.origin + ray.direction * t_result;

	Vec3 normals[] = { 
		X, X * -1.0f,
		Y, Y * -1.0f,
		Z, Z * -1.0f
	};

	for (int i = 0; i < 6; ++i) {
		if (compare(t_result, t[i])) {
			result.normal = normals[i].GetNormalized();
		}
	}
	
	return true;
}


bool Raycast(const Triangle & triangle, const Ray & ray, RaycastResult & result)
{
	result.Reset();

	Plane plane = FromTriangle(triangle);
	RaycastResult planeResult;

	if (!Raycast(plane, ray, planeResult)) {
		return false;
	}

	float t = planeResult.t;
	Point3D resultPoint = ray.origin + ray.direction * t;
	Vec3 barycentric = Barycentric(resultPoint, triangle);

	if (barycentric.x >= 0.0f && barycentric.x <= 1.0f &&
		barycentric.y >= 0.0f && barycentric.y <= 1.0f &&
		barycentric.z >= 0.0f && barycentric.z <= 1.0f) {

		result.t = t;
		result.hit = true;
		result.point = ray.origin + ray.direction *t;
		result.normal = plane.normal;

		return true;
	}
	return false;
}
