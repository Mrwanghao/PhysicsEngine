#pragma once
#include "Rigidbody.h"
#include <vector>
#include "CollisionManfold.h"

class PhysicsSystem
{
protected:
	std::vector<Rigidbody*> bodies;
	std::vector<OBB> constraints;
	std::vector<Rigidbody*> colliders1;
	std::vector<Rigidbody*> colliders2;
	std::vector<CollisionManifold> results;

public:
	bool LinearProjection;//是否线性矫正
	int ImpulseIteration; //一次解决多少一个冲撞
	float PenetrationSlack;
	float LinearProjectionPercent;

public:
	PhysicsSystem();
	void Update(float deltaTime);
	void Render();

	void AddRigidbody(Rigidbody* body);
	void AddConstraints(const OBB& constraint);
	void ClearRigidbodys();
	void ClearConstraints();
};