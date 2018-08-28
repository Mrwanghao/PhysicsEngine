#include "GLWindow.h"
#include <string>
#include "glad/glad.h"
#include "MathUtil.h"

GLWindow::GLWindow(const char * title, int width, int height)
	:
	IWindow(title, width, height)
{
}

void GLWindow::SetClearColor(float r, float g, float b)
{
	r = clamp(r, 0.0f, 1.0f);
	b = clamp(b, 0.0f, 1.0f);
	g = clamp(g, 0.0f, 1.0f);
	glClearColor(r, g, b, 1.0f);
}

void GLWindow::OnInitialize()
{
	glClearColor(0.5f, 0.6f, 0.7f, 1.0f);

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);

	OnResize(width, height);
}

void GLWindow::OnRender()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
}

void GLWindow::OnResize(int width, int height)
{
	glViewport(0, 0, width, height);
}

void GLWindow::SetGLProjection(float * projectionArray)
{
	glMatrixMode(GL_PROJECTION);
	glLoadMatrixf(projectionArray);
}

void GLWindow::SetGLModelView(float * mvArray)
{
	glMatrixMode(GL_MODELVIEW);
	glLoadMatrixf(mvArray);
}
