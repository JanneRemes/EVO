#include "Platform/Window.h"


Window::Window(void)
{
}


Window::~Window(void)
{
    glfwTerminate();
}

int Window::createWindow(int height, int width,const char* name)
{
    if (!glfwInit())
        return -1;

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);

	window = glfwCreateWindow(height, width, name , NULL, NULL);
    if (!window)
    {
        glfwTerminate();
		return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);
	
	
	glewExperimental = GL_TRUE;
	// TODO: implement error checking properly
	GLenum res = glewInit();

	const GLubyte* string = glewGetErrorString(res);


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

void Window::SwapBuffers()
{
	glfwSwapBuffers(window);
}