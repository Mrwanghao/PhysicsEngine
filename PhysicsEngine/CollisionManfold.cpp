#include "CollisionManfold.h"
#include "math3d.h"


void CollisionManifold::Reset()
{
	colliding = false;
	normal = Vec3(0, 0, 1);
	depth = FLT_MAX;
	if (contacts.size() > 0) {
		contacts.clear();
	}
}

void Reset(CollisionManifold * fold)
{
	fold->colliding = false;
	fold->normal = Vec3(0, 0, 1);
	fold->depth = FLT_MAX;
	if (fold->contacts.size() > 0) {
		fold->contacts.clear();
	}
}

CollisionManifold FindCollisionFeatures(const Sphere & A, const Sphere & B)
{
	CollisionManifold result;
	result.Reset();

	float rsum = A.radius + B.radius;
	Vec3 distance = B.center - A.center;
	
	if (distance.MagnitudeSq() - rsum * rsum > 0.0f || compare(distance.MagnitudeSq(), 0.0f))
	{
		return result;
	}

	result.colliding = true;
	result.normal = distance.GetNormalized();
	result.depth = fabsf(distance.Magnitude() - rsum) * 0.5f;

	float dtp = A.radius - result.depth;
	Point3D contact = A.center + distance * dtp;
	result.contacts.push_back(contact);

	return result;
}

CollisionManifold FindCollisionFeatures(const OBB & A, const Sphere & B)
{
	CollisionManifold result;
	result.Reset();

	Point3D closestPoint = ClosestPointInOBB(A, B.center);
	float distanceSq = (closestPoint - B.center).MagnitudeSq();
	if (distanceSq > B.radius * B.radius) {
		return result;
	}

	Vec3 normal;
	//��������������
	if (compare(distanceSq, 0.0f)) {
		float mSq = (closestPoint - A.origin).MagnitudeSq();
		//���������ĺܽ�������������Ҳ�ܽ�
		if (compare(mSq, 0.0f)) {
			return result;
		}
		normal = (closestPoint - A.origin).GetNormalized();
	}
	else {
		normal = (B.center - closestPoint).GetNormalized();
	}
	
	//��Ϊǰ��ʹ�õ��Ƿ���
	Point3D outsidePoint = B.center - normal * B.radius;
	float distance = (closestPoint - outsidePoint).Magnitude();
	result.colliding = true;
	result.contacts.push_back(closestPoint + (outsidePoint - closestPoint) * 0.5f);
	result.normal = normal;
	result.depth = distance * 0.5f;
	return result;
}

CollisionManifold FindCollisionFeatures(const OBB & A, const OBB & B)
{
	CollisionManifold result;
	result.Reset();
	
	const float* o1 = A.orientation.data;
	const float* o2 = B.orientation.data;

	Vec3 test[15] = {
		Vec3(o1[0], o1[1], o1[2]),
		Vec3(o1[3], o1[4], o1[5]),
		Vec3(o1[6], o1[7], o1[8]),
		Vec3(o2[0], o2[1], o2[2]),
		Vec3(o2[3], o2[4], o2[5]),
		Vec3(o2[6], o2[7], o2[8])
	};

	for (int i = 0; i < 3; ++i) { 
		test[6 + i * 3 + 0] = test[i + 3].Cross(test[0]);
		test[6 + i * 3 + 1] = test[i + 3].Cross(test[1]);
		test[6 + i * 3 + 2] = test[i + 3].Cross(test[2]);
	}

	Vec3 * hitNormal = 0;
	bool shouldFlip;
	
	for (int i = 0; i < 15; ++i) {
		//��ֹ������ƽ�м�������Ĳ��
		if (test[i].MagnitudeSq() < 0.001f) {
			continue;
		}
		
		float depth = PenetrationDepth(A, B, test[i], &shouldFlip);
		
		//����ײ
		if (depth <= 0.0f) {
			return result;
		}
		//��ײ���С��ǰ������
		else if (depth < result.depth) {
			//�Ƿ��������ײ��  ��ô�ͷ���
			if (shouldFlip) {
				test[i] = test[i] * -1.0f;
			}
			
			result.depth = depth;
			hitNormal = &test[i];
		}
	}
	
	//���������Ҫ��Ϊ���ҵ���15�������ϲ�����ǳ���ĸ�����

	if (hitNormal == 0) {
		return result;
	}
	Vec3 axis = hitNormal->GetNormalized();
	
	//�����������֮�����ײ��
	std::vector<Point3D> c1 = ClipEdgesToOBB(GetEdges(B), A);
	std::vector<Point3D> c2 = ClipEdgesToOBB(GetEdges(A), B);
	result.contacts.reserve(c1.size() + c2.size());

	//����������ײ�������
	result.contacts.insert(result.contacts.end(), c1.begin(), c1.end());
	result.contacts.insert(result.contacts.end(), c2.begin(), c2.end());
	
	Interval2D i = GetInterval(A, axis);
	float distance = (i.max - i.min) * 0.5f - result.depth * 0.5f;
	Vec3 pointOnPlane = A.origin + axis * distance;
	
	//����һ����Щ��Ͷ�䵽һ��ƽ����ȥ ԭ���ĵ���obb���� ����������Ҫ�����Ƕ���ͶӰ����д ���ͶӰ����ڲ�����ȵ��м�
	for (int i = result.contacts.size() - 1; i >= 0; --i) 
	{
		Vec3 contact = result.contacts[i];
		result.contacts[i] = contact + (axis * axis.Dot(pointOnPlane - contact));

		//ȥ���ظ���������Ƶ�
		for (int j = result.contacts.size() - 1; j > i; --j) {
			if ((result.contacts[j] - result.contacts[i]).MagnitudeSq() < 0.0001f) {
				result.contacts.erase(result.contacts.begin() + j);
				break;
			}
		}
	}
	
	result.colliding = true;
	result.normal = axis;
	return result;
}

std::vector<Point3D> GetVertices(const OBB & obb)
{
	std::vector<Point3D> vertices;
	vertices.resize(8);
	Vec3 C = obb.origin;
	Vec3 E = obb.size;
	const float* orientation = obb.orientation.data;

	Vec3 A[] =
	{
		Vec3(orientation[0], orientation[1], orientation[2]),
		Vec3(orientation[3], orientation[4], orientation[5]),
		Vec3(orientation[6], orientation[7], orientation[8])
	};

	vertices[0] = C + A[0] * E[0] + A[1] * E[1] + A[2] * E[2];
	vertices[1] = C - A[0] * E[0] + A[1] * E[1] + A[2] * E[2];
	vertices[2] = C + A[0] * E[0] - A[1] * E[1] + A[2] * E[2];
	vertices[3] = C + A[0] * E[0] + A[1] * E[1] - A[2] * E[2];
	vertices[4] = C - A[0] * E[0] - A[1] * E[1] - A[2] * E[2];
	vertices[5] = C + A[0] * E[0] - A[1] * E[1] - A[2] * E[2];
	vertices[6] = C - A[0] * E[0] + A[1] * E[1] - A[2] * E[2];
	vertices[7] = C - A[0] * E[0] - A[1] * E[1] + A[2] * E[2];

	return vertices;
}

std::vector<Line> GetEdges(const OBB & obb)
{
	std::vector<Line> result;
	result.reserve(12);
	std::vector<Point3D> v = GetVertices(obb);

	int index[][2] = { 
		{ 6, 1 },{ 6, 3 },{ 6, 4 },{ 2, 7 },{ 2, 5 },{ 2, 0 },
		{ 0, 1 },{ 0, 3 },{ 7, 1 },{ 7, 4 },{ 4, 5 },{ 5, 3 }
	};

	for (int j = 0; j < 12; ++j) {
		result.push_back(Line(
			v[index[j][0]], v[index[j][1]]
		));
	}

	return result;
}

std::vector<Plane> GetPlanes(const OBB & obb)
{
	Vec3 c = obb.origin;
	Vec3 e = obb.size;
	const float* o = obb.orientation.data;
	Vec3 a[] = {
		Vec3(o[0], o[1], o[2]),
		Vec3(o[3], o[4], o[5]),
		Vec3(o[6], o[7], o[8])
	};

	std::vector<Plane> result;
	result.resize(6);

	result[0] = Plane(a[0]		  ,  a[0].Dot((c + a[0] * e.x)));
	result[1] = Plane(a[0] * -1.0f, -a[0].Dot((c - a[0] * e.x)));
	result[2] = Plane(a[1]		  ,  a[1].Dot((c + a[1] * e.y)));
	result[3] = Plane(a[1] * -1.0f, -a[1].Dot((c - a[1] * e.y)));
	result[4] = Plane(a[2]		  ,  a[2].Dot((c + a[2] * e.z)));
	result[5] = Plane(a[2] * -1.0f, -a[2].Dot((c - a[2] * e.z)));

	return result;
}

std::vector<Point3D> ClipEdgesToOBB(const std::vector<Line>& edges, const OBB & obb)
{
	std::vector<Point3D> result;
	result.reserve(edges.size());
	Point3D intersection;
	std::vector<Plane> planes = GetPlanes(obb);

	for (int i = 0; i < planes.size(); ++i) {
		for (int j = 0; j < edges.size(); ++j) {
			if (ClipToPlane(planes[i], edges[j], &intersection)) {
				if (PointInOBB(intersection, obb)) {
					result.push_back(intersection);
				}
			}
		}
	}
	return result;
}

//����������ĳ�������ϲ����˶���
float PenetrationDepth(const OBB & o1, const OBB & o2, const Vec3 & axis, bool * outShouldFlip)
{
	Interval2D i1 = GetInterval(o1, axis.GetNormalized());
	Interval2D i2 = GetInterval(o2, axis.GetNormalized());
	
	if (!((i2.min <= i1.max) && (i1.min <= i2.max))) {
		return 0.0f; 
	}
	
	float len1 = i1.max - i1.min;
	float len2 = i2.max - i2.min;
	
	float min = fminf(i1.min, i2.min);
	float max = fmaxf(i1.max, i2.max);
	
	float length = max - min;
	
	if (outShouldFlip != 0) {
		*outShouldFlip = (i2.min < i1.min);
	}
	
	return (len1 + len2) - length;
}
