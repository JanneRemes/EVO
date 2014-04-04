#include "Platform/debug.h"
#include "Platform/Window.h"
#include "Platform/Texture.h"
#include "Include/Engine.h"
#include "Platform/Input.h"
#include "Platform/New.h"
#include "Platform/Leak.h"

float getTotalTime();
int main(void)
{
	writeLog("main");
	Leak leak;

    /* Initialize the library */
	int Width = 700;
	int Height = 1000;

	Window* window = EVO_NEW Window();
	window->createWindow(Height,Width,"I made dis");
	Engine* engine;
	engine = EVO_NEW Engine();
	engine->init();

	float deltaTime = 0.0f;
	float newTime = 0.0f;
	float oldTime = 0.0f;

    /* Create a windowed mode window and its OpenGL context */
	while(window->isOpen())
	{
		oldTime = newTime;
		newTime = getTotalTime();
		deltaTime = newTime - oldTime;
		window->pollEvents();
		engine->update();
		engine->draw();
		window->SwapBuffers();
	}
	delete engine;
	delete window;
    return 0;
}

float getTotalTime()
{
	return glfwGetTime();
}