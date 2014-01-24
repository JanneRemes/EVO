#include "Window.h"


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

  //  /* Loop until the user closes the window */
  //  while (!glfwWindowShouldClose(window))
  //  {
  //      /* Render here */

		////engine->update();

  //      /* Swap front and back buffers */
  //      glfwSwapBuffers(window);

  //      /* Poll for and process events */
  //      glfwPollEvents();
  //  }
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