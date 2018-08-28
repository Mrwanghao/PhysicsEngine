#pragma once
#include "GLWindow.h"

class BaseMod;


class Window : public GLWindow
{
protected:
	BaseMod * mod;

protected:
	void ApplyDemoCamera();

public:
	Window(const char* title, int width, int height)
		: 
		GLWindow(title, width, height)
	{
		fixedFPS = 30.0f;
		targetFPS = 60.0f;
	}

	virtual ~Window();

	virtual void OnInitialize();
	virtual void OnRender();
	virtual void OnResize(int width, int height);
	virtual void OnFixedUpdate(float deltaTime);
	virtual void OnUpdate(float deltaTime);
	virtual void OnShutdown();

	void StopMod();
	void StartMod();
};