#pragma once
#include "BaseMod.h"
#include "PhysicsSystem.h"
#include "RigidbodyVolume.h"


class CubeMod : public BaseMod
{
protected:
	PhysicsSystem physicsSystem;
	std::vector<RigidbodyVolume> bodies;
	RigidbodyVolume groundBox;

protected:
	void ResetDemo();
public:
	virtual void OnInitialize(int width, int height);
	virtual void OnRender();
	virtual void OnUpdate(float dt);
};

