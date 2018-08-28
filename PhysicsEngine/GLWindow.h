#pragma once


#include "IWindow.h"
#include "Vec2.h"


class GLWindow : public IWindow
{
public:
	GLWindow(const char* title, int width, int height);
	virtual ~GLWindow() { }
	void SetClearColor(float r, float g, float b);

	virtual void OnInitialize();
	virtual void OnRender();
	virtual void OnResize(int width, int height);
	
	void SetGLProjection(float* projectionArray);
	void SetGLModelView(float* mvArray);

};
