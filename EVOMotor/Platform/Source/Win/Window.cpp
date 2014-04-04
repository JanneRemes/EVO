#include "Platform/Window.h"
#include "Platform/debug.h"

GLFWwindow* Window::window = 0;
int Window::winWidth = 0;
int Window::winHeight = 0;

Window::Window(void)
{
	wHeigth = 0;
	wWidth = 0;
}

Window::~Window(void)
{
    glfwTerminate();
}

int Window::createWindow(int height, int width,const char* name)
{
    if (!glfwInit())
        return -1;

	winWidth = width;
	winHeight = height;

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);

	window = glfwCreateWindow(width, height, name , NULL, NULL);
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

	glfwSetWindowSizeCallback(Window::window, window_size_callback);

	return 0;
}

bool Window::isOpen()
{
	return !glfwWindowShouldClose(window);
}

void Window::pollEvents()
{
    glfwPollEvents();
}

void Window::SwapBuffers()
{
	glfwSwapBuffers(window);
}

glm::vec2 Window::getWindowSize()
{
	glfwGetWindowSize(Window::window, &wWidth, &wHeigth);
	return glm::vec2((float)wWidth,(float)wHeigth);
}

void Window::window_size_callback(GLFWwindow* window, int width, int height)
{
	winWidth = width;
	winHeight = height;
	glViewport(0,0,width,height);
}

