#include "BaseMod.h"

BaseMod::BaseMod()
{
	size = Vec2(0.0f, 0.0f);
}

void BaseMod::OnInitialize(int width, int height)
{
	Matrix4 world;
	world =
	{
		1.0f, 0.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f, 0.0f,
		0.0f, 10.0f, -10.0f, 0.0f
	};
	camera.SetWorld(world);

	OnResize(width, height);
}

void BaseMod::OnResize(int width, int height)
{
	camera.Perspective(60.0f, (float)width / (float)height, 0.01f, 1000.0f);
	size = Vec2(width, height);
}

void BaseMod::OnRender()
{
}

void BaseMod::OnUpdate(float dt)
{
	camera.Update(dt);
}

