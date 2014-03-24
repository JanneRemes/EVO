#include "Platform/Android/Window.h"

int Window::winHeight = 800;
int Window::winWidth = 480;

Window::Window(void)
{
	winHeight = 800;
	winWidth = 480;
}

Window::~Window(void)
{
}

int Window::createWindow(int height, int width,const char* name)
{
	winHeight = 800;
	winWidth = 480;
}