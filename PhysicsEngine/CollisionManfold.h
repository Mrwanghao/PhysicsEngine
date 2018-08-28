#pragma once
#include "Vec3.h"
#include <vector>
#include "Sphere.h"
#include "OBB.h"
#include "Line.h"
#include "Plane.h"

class CollisionManifold
{
public:
	bool colliding;
	Vec3 normal;
	float depth;
	std::vector<Vec3> contacts; //Åö×²µã
	void Reset();
};

void Reset(CollisionManifold* fold);

CollisionManifold FindCollisionFeatures(const Sphere& A, const Sphere& B);
CollisionManifold FindCollisionFeatures(const OBB& A, const Sphere& B);
CollisionManifold FindCollisionFeatures(const OBB& A, const OBB& B);


std::vector<Point3D> GetVertices(const OBB& obb);
std::vector<Line> GetEdges(const OBB& obb);
std::vector<Plane> GetPlanes(const OBB& obb);
bool ClipToPlane(const Plane& plane, const Line& line, Point3D* outPoint);
std::vector<Point3D> ClipEdgesToOBB(const std::vector<Line>& edges, const OBB& obb);
float PenetrationDepth(const OBB& o1, const OBB& o2, const Vec3& axis, bool* outShouldFlip);







