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
	bool LinearProjection;//�Ƿ����Խ���
	int ImpulseIteration; //һ�ν������һ����ײ
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