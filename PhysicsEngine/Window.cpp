#include "Window.h"
#include "BaseMod.h"
#include "CubeMod.h"

static Window modwindow("PhysicsEngine", 800, 600);

void Window::ApplyDemoCamera()
{
	if (mod == 0) {
		return;
	}

	Matrix4 projection = mod->camera.GetProjMat();
	Matrix4 view = mod->camera.GetViewMat();

	SetGLProjection(projection.data);
	//SetGLModelView(view.data);
}

Window::~Window()
{
	StopMod();
}

void Window::OnInitialize()
{
	GLWindow::OnInitialize();
}

void Window::OnResize(int width, int height)
{
	GLWindow::OnResize(width, height);
	if (mod != 0)
	{
		mod->OnResize(width, height);
	}
	ApplyDemoCamera();
}

void Window::OnRender()
{
	GLWindow::OnRender();
	if (mod != 0)
	{
		//Matrix4 view = mod->camera.GetViewMat();
		//SetGLModelView(view.data);
		mod->OnRender();
	}
}

void Window::OnFixedUpdate(float deltaTime)
{
	GLWindow::OnFixedUpdate(deltaTime);
	if (mod != 0) {
		mod->OnUpdate(deltaTime);
	}
}

void Window::OnUpdate(float deltaTime)
{
	GLWindow::OnUpdate(deltaTime);
}

void Window::OnShutdown()
{
	GLWindow::OnShutdown();
	StopMod();
}

void Window::StopMod()
{
	GLWindow::OnShutdown();
	if (mod != 0)
	{
		mod->OnShutdown();
		delete mod;
		mod = 0;
	}
}

void Window::StartMod()
{
	StopMod();
	mod = new CubeMod();
	mod->OnInitialize(GetWidth(), GetHeight());
	ApplyDemoCamera();
}
