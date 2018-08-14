#include "IWindow.h"




IWindow* IWindow::Singleton = nullptr;


IWindow::IWindow() 
	:
	quitFlag(false), 
	fullFlag(false),
	width(800), 
	height(600), 
	title(0), 
	titleDirty(false), 
	targetFPS(30), 
	fixedFPS(30), 
	visible(false)
{}

IWindow::IWindow(const char* title)
{}