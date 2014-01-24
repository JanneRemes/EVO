#include "debug.h"

#include "Window.h"
int main(void)
{
    /* Initialize the library */
    if (!glfwInit())
        return -1;

	Window* window = new Window();
	window->CreateWindow(500,500,"I made this T:Maker");

    /* Create a windowed mode window and its OpenGL context */

	while(window->isOpen())
	{
		//engine->update();
		window->pollEvents();

	}

    glfwTerminate();
    return 0;
}