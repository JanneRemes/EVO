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
	window->CreateWindow(500,500,"I made dis");
	Engine* engine;
	engine = new Engine;
	engine->init();

    /* Create a windowed mode window and its OpenGL context */

	//Texture* texture = new Texture("Assets/");
	//tgaHeader header;
	//texture->loadTGA("kuva.tga",header);

	while(window->isOpen())
	{
		window->pollEvents();
		engine->update();
		engine->draw(window->window);
	}

    glfwTerminate();
    return 0;
}