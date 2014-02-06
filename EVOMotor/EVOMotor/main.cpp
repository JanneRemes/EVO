#include "Platform/debug.h"
#include "Platform/Window.h"
#include "Platform/Texture.h"
#include "Include/Engine.h"

int main(void)
{
    /* Initialize the library */
    if (!glfwInit())
        return -1;


	Window* window = new Window();
	window->CreateWindow(Engine::windowWidth,Engine::windowHeight,"I made dis");
	Engine* engine;
	engine = new Engine;
	engine->init();

    /* Create a windowed mode window and its OpenGL context */
	while(window->isOpen())
	{
		window->pollEvents();
		engine->update();
		engine->draw(window->window);
	}

	delete engine;
    glfwTerminate();
    return 0;
}