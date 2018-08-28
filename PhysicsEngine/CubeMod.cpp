#include "CubeMod.h"

void CubeMod::ResetDemo()
{
	physicsSystem.ClearRigidbodys();
	physicsSystem.ClearConstraints();

	bodies.clear();
	bodies.resize(2);

	bodies[0].type = BOX;
	bodies[0].position = Vec3(0.0f, 0.0f, 50);
	bodies[0].orientation = Vec3(0.0f, 0.0f, 20.0f);

	bodies[1].type = BOX;
	bodies[1].position = Vec3(0, -10, 50);
	bodies[1].mass = 5.0f;

	groundBox = RigidbodyVolume(BOX);
	groundBox.position = Vec3(0, -20.0f, 50);
	groundBox.box.size = Vec3(50, 1, 50) * 0.25f;
	groundBox.mass = 0.0f;
	groundBox.SynchCollisionVolumes();

	for (int i = 0; i < bodies.size(); ++i) {
		bodies[i].SynchCollisionVolumes();
		physicsSystem.AddRigidbody(&bodies[i]);
	}
	physicsSystem.AddRigidbody(&groundBox);
}

void CubeMod::OnInitialize(int width, int height)
{
	BaseMod::OnInitialize(width, height);

	physicsSystem.ImpulseIteration = 16;
	physicsSystem.LinearProjection = true;

	ResetDemo();
}

void CubeMod::OnRender()
{
	BaseMod::OnRender();
	physicsSystem.Render();
}

void CubeMod::OnUpdate(float dt)
{
	BaseMod::OnUpdate(dt);
	physicsSystem.Update(dt);
}
