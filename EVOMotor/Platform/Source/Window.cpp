#include "Platform/Window.h"


Window::Window(void)
{
}


Window::~Window(void)
{
    glfwTerminate();
}

int Window::CreateWindow(int height, int width,const char* name)
{
	glewExperimental = GL_TRUE;
	glewInit();
	
    if (!glfwInit())
        return -1;

	window = glfwCreateWindow(height, width, name , NULL, NULL);
    if (!window)
    {
        glfwTerminate();
		return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);


	return 0;
}

bool Window::isOpen()
{
	return !glfwWindowShouldClose(window);
}

void Window::pollEvents()
{
	//swapbuffer
    glfwPollEvents();
}