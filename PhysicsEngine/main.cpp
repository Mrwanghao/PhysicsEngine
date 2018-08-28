#include <iostream>
#include "glad/glad.h"
#include <glfw/glfw3.h>
#include "Window.h"
#include "MathUtil.h"
#include "OBB.h"
#include "draw.h"

extern Window modwindow("PhysicsEngine", 800, 600);



int main()
{
	

	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_COMPAT_PROFILE);
	GLFWwindow* window = glfwCreateWindow(800, 600, "OpenGLShader", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "创建窗口失败" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "初始化GLAD失败" << std::endl;
		return -1;
	}

	Matrix4 projection = Projection(60.0f, 4.0f / 3.0f, 0.1f, 1000.0f);
	glMatrixMode(GL_PROJECTION);
	glLoadMatrixf(projection.data);

	modwindow.StartMod();

	OBB obb(Vec3(0.0f, 0.0f, 10.0f), Vec3(1.0f, 1.0f, 1.0f));

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	float val[] = { 0.5f, 10.0f, 0.5f, 0.0f };
	glLightfv(GL_LIGHT0, GL_POSITION, val);

	glEnable(GL_DEPTH_TEST);

	while (!glfwWindowShouldClose(window))
	{
		Sleep(33);
		modwindow.OnFixedUpdate(0.05f);
		modwindow.OnRender();
		
		//RenderOBB(obb);
		glfwSwapBuffers(window);
		glfwPollEvents();
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	glfwTerminate();
	return 0;
}

