#include "Include/Engine.h"

int Engine::windowWidth = 700;
int Engine::windowHeight = 500;

Engine::Engine(void)
{
}

Engine::~Engine(void)
{
	delete graphics;
	delete shader;
	delete sprite;
	delete viewport;
}

void Engine::init()
{
	tgaHeader header;
	graphics = new Graphics(windowWidth,windowHeight);
	texture = Texture::load("Assets/Waluigi.tga");
	shader = new Shader("Assets/Shaders/basic.vert", "Assets/Shaders/basic.frag");

	//graphics->init();
	fileReader->loadFile("Assets/imadethis.txt");

	/*texture loadTGA("Assets/kuva.tga",header);*/

	sprite = new SpriteObject(200, 200, 200, 200, texture, shader);
	viewport = new Viewport((float)windowWidth,(float)windowHeight);

	red = 0;
	blue = 0;
	green = 0;
}

void Engine::update()
{
	red = rand()%2+0.01f;
	blue = rand()%2+0.01f;
	green = rand()%2+0.01f;

	sprite->setPosition(rand()%10+100,rand()%10+100);
	sprite->setRotationZ(rand()%10);
	sprite->setColor(glm::vec4(red,green,blue,1.f));
}

void Engine::draw(GLFWwindow* window)
{
	
	graphics->clear(1.0f,0.0f,1.0f);

	viewport->draw(sprite);

	graphics->draw(window);
}

float Engine::getTotalTime()
{
	return glfwGetTime();
}