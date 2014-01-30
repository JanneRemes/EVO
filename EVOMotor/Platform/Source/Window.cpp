#include "Platform/Window.h"


Window::Window(void)
{
}


Window::~Window(void)
{
}

int Window::CreateWindow(int height, int width,const char* name)
{
	window = glfwCreateWindow(height, width, name , NULL, NULL);
    if (!window)
    {
        glfwTerminate();
		return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

	glewExperimental = GL_TRUE;
	glewInit();

	return 0;
}

bool Window::isOpen()
{
	return !glfwWindowShouldClose(window);
}

void Window::pollEvents()
{
	glfwSwapBuffers(window);
    glfwPollEvents();
}