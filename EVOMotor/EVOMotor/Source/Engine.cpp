#include "Include/Engine.h"

int Engine::windowWidth = 700;
int Engine::windowHeight = 500;

Engine::Engine(void)
{
}

Engine::~Engine(void)
{
	delete graphics;
}

void Engine::update()
{
}

void Engine::draw(GLFWwindow* window)
{
	graphics->draw(window);
	graphics->clear(1.0f,0.0f,1.0f);
}

void Engine::init()
{

	graphics = new Graphics(windowWidth,windowHeight);

	graphics->init();
	fileReader->loadFile("Assets/imadethis.txt");

	tgaHeader header;
	texture->loadTGA("Assets/kuva.tga",header);

}