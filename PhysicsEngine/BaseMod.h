#pragma once
#include "OrbitCamera.h"
#include "Vec2.h"

class BaseMod
{
private:
	//²»¿É¿½±´
	BaseMod(const BaseMod& right);
	BaseMod& operator=(const BaseMod& right);
protected:
	Vec2 size;
	
public:
	OrbitCamera camera;

	BaseMod();
	inline virtual ~BaseMod() { }

	virtual void OnInitialize(int width, int height);
	virtual void OnResize(int width, int height);
	virtual void OnRender();
	virtual void OnUpdate(float dt);
	virtual void OnShutdown() {}

};









