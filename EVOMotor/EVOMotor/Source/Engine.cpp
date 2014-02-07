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

void Engine::init()
{
	graphics = new Graphics(windowWidth,windowHeight);

	shader = new Shader("Assets/Shaders/basic.vert", "Assets/Shaders/basic.frag");

	graphics->init();
	fileReader->loadFile("Assets/imadethis.txt");

	tgaHeader header;
	texture->loadTGA("Assets/kuva.tga",header);

	sprite = new SpriteObject(10, 10, 100, 100, texture, shader);


}

void Engine::update()
{
}

void Engine::draw(GLFWwindow* window)
{
	graphics->draw(window);
	graphics->clear(1.0f,0.0f,1.0f);
}

float Engine::getTotalTime()
{
	return glfwGetTime();
}