#include "PhysicsSystem.h"
#include "draw.h"
#include "RigidbodyVolume.h"

PhysicsSystem::PhysicsSystem()
{
	ImpulseIteration = 5.0f;
	LinearProjectionPercent = 0.45f;
	PenetrationSlack = 0.01f;
	LinearProjection = true;

	colliders1.reserve(100);
	colliders2.reserve(100);
	results.reserve(100);
}

void PhysicsSystem::Update(float deltaTime)
{
	colliders1.clear();
	colliders2.clear();
	results.clear();

	CollisionManifold result;
	for (int i = 0; i < bodies.size(); i++)
	{
		for (int j = i; j < bodies.size(); j++)
		{
			if (i == j)
				continue;

			result.Reset();

			if (bodies[i]->HasVolume() && bodies[j]->HasVolume())
			{
				RigidbodyVolume* m1 = (RigidbodyVolume*)bodies[i];
				RigidbodyVolume* m2 = (RigidbodyVolume*)bodies[j];
				result = FindCollisionFeatures(*m1, *m2);

			}

			if (result.colliding)
			{
				colliders1.push_back(bodies[i]);
				colliders2.push_back(bodies[j]);
				results.push_back(result);
			}
		}
	}

	//重力添加
	for (int i = 0, size = bodies.size(); i < size; i++)
	{
		bodies[i]->ApplyForces();
	}

	//对每个接触点进行力的作用
	for (int k = 0; k < ImpulseIteration; k++)
	{
		for (int i = 0; i < results.size(); i++)
		{
			for (int j = 0; j < results[i].contacts.size(); j++)
			{
				RigidbodyVolume* m1 = (RigidbodyVolume*)colliders1[i];
				RigidbodyVolume* m2 = (RigidbodyVolume*)colliders2[i];
				ApplyImpulse(*m1, *m2, results[i], j);
			}
		}
	}

	//更新速度位置
	for (int i = 0; i < bodies.size(); i++)
	{
		bodies[i]->Update(deltaTime);
	}

	if (LinearProjection) {
		for (int i = 0, size = results.size(); i < size; ++i) {
			if (!colliders1[i]->HasVolume() && !colliders2[i]->HasVolume()) {
				continue;
			}

			RigidbodyVolume* m1 = (RigidbodyVolume*)colliders1[i];
			RigidbodyVolume* m2 = (RigidbodyVolume*)colliders2[i];
			float totalMass = m1->InvMass() + m2->InvMass();

			//两个物体体积都特别的大
			if (compare(totalMass, 0.0f)) {
				continue;
			}

			float depth = fmaxf(results[i].depth - PenetrationSlack, 0.0f);
			float scalar = (compare(totalMass, 0.0f)) ? 0.0f : depth / totalMass;
			Vec3 correction = results[i].normal * scalar * LinearProjectionPercent;

			m1->position = m1->position - correction * m1->InvMass();
			m2->position = m2->position + correction * m2->InvMass();

			m1->SynchCollisionVolumes();
			m2->SynchCollisionVolumes();
		}
	}

	for (int i = 0; i < bodies.size(); i++)
	{
		//仅仅对particle有用 而且做的处理是 对他速度反弹处理 位置往上移动一点
		bodies[i]->SolveConstraints(constraints);
	}
}

void PhysicsSystem::Render()
{
	for (int i = 0; i < bodies.size(); i++)
	{
		bodies[i]->Render();
	}

	for (int i = 0; i < constraints.size(); i++)
	{
		RenderOBB(constraints[i]);
	}
}

void PhysicsSystem::AddRigidbody(Rigidbody * body)
{
	bodies.push_back(body);
}

void PhysicsSystem::AddConstraints(const OBB & constraint)
{
	constraints.push_back(constraint);
}

void PhysicsSystem::ClearRigidbodys()
{
	bodies.clear();
}

void PhysicsSystem::ClearConstraints()
{
	constraints.clear();
}
