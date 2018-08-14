#pragma once
#include "Rigidbody.h"
#include "Sphere.h"
#include "Matrix4.h"
#include "CollisionManfold.h"



//体积体 代表的是 一个比较实例的物体
class RigidbodyVolume : public Rigidbody
{
public:
	Vec3 position;
	Vec3 velocity;

	Vec3 orientation;
	Vec3 angVelocity;

	Vec3 forces;
	//扭力
	Vec3 torques;

	float mass;
	//系数
	float cor;

	float friction;
	OBB box;
	Sphere sphere;

public:
	inline RigidbodyVolume()
		:
		cor(0.5f),
		mass(1.0f),
		friction(0.5f)
	{
		type = BASE;
	}

	inline RigidbodyVolume(int bodyType)
		:
		cor(0.5f),
		mass(1.0f),
		friction(0.6f)
	{
		type = bodyType;
	}

	virtual ~RigidbodyVolume() {}

	virtual void Render();
	virtual void Update(float dt);
	float InvMass();
	Matrix4 InvTensor();
	virtual void ApplyForces();
	void SynchCollisionVolumes();
	virtual void AddLinearImpulse(const Vec3& impulse);
	virtual void AddRotationalImpulse(const Vec3& point, const Vec3& impulse);



};

CollisionManifold FindCollisionFeatures(RigidbodyVolume& ra, RigidbodyVolume& rb);
void ApplyImpulse(RigidbodyVolume& a, RigidbodyVolume& b, const CollisionManifold& m, int c);