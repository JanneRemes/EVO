#include "Include/Engine.h"


Engine::Engine(void)
{
}

void Engine::update()
{

}

void Engine::draw(GLFWwindow* window)
{
	glfwSwapBuffers(window);
	graphics->clear(1.0f,0.0f,1.0f);
}

void Engine::init()
{
	graphics->init();
}

Engine::~Engine(void)
{
}
