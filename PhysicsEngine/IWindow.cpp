#include "IWindow.h"
#include <iostream>
#include <string>


IWindow* IWindow::Singleton = nullptr;


IWindow::IWindow() 
	:
	width(800), 
	height(600), 
	title(0), 
	titleDirty(false), 
	targetFPS(30), 
	fixedFPS(30)
{
	if (Singleton != 0) {
		std::cout << "Error, two instances of the window interface exist!\n";
	}

	SetTitle("Physics Engine");
	titleDirty = true;
	Singleton = this;
}

IWindow::IWindow(const char* _title)
	:
	width(800),
	height(600),
	title(0),
	titleDirty(false),
	targetFPS(30),
	fixedFPS(30)
{
	if (Singleton != 0) {
		std::cout << "Error, two instances of the window interface exist!\n";
	}

	SetTitle(_title);
	titleDirty = true;
	Singleton = this;
}

IWindow::IWindow(const char * _title, int _width, int _height)
	:
	width(_width),
	height(_height),
	title(0),
	titleDirty(false),
	targetFPS(30),
	fixedFPS(30)
{
	if (Singleton != 0) {
		std::cout << "Error, two instances of the window interface exist!\n";
	}

	SetTitle(_title);
	titleDirty = true;
	Singleton = this;
}

IWindow::~IWindow()
{
	CleanupMemory(this);
}

void IWindow::SetTitle(const char * _title)
{
	if (title != 0) {
		free(title);
	}

	int len = strlen(_title);
	title = (char*)malloc(sizeof(char) * len + 1);
	strcpy(title, _title);
	title[len] = '\0';
	titleDirty = true;
}

bool IWindow::GetAndResetTitleDirtyFlag()
{
	bool value = titleDirty;
	titleDirty = false;
	return value;
}

void CleanupMemory(IWindow * window)
{
	if (window->title != 0)
	{
		free(window->title);
		window->title = 0;
	}
}
