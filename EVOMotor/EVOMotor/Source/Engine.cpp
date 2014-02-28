#include "Include/Engine.h"
#include "Platform/debug.h"

#include <iostream>
#include <time.h>


int Engine::windowWidth = 700;
int Engine::windowHeight = 500;

Engine::Engine(void)
{
	initialized = false;
}

Engine::~Engine(void)
{
	delete graphics;
	delete shader;
	delete viewport;
}

bool Engine::isInit()
{
	return initialized;
}

void Engine::init()
{
	graphics = new Graphics(windowWidth,windowHeight);
	viewport = new Viewport((float)windowWidth,(float)windowHeight);
	spriteBatch = new SpriteBatch();
	shader = new Shader("Assets/Shaders/basic.vert", "Assets/Shaders/basic.frag");
	
	spriteBatch->init(shader);
	spriteBatch->addObject("Assets/Waluigi.tga",200,200,200,200);
	spriteBatch->addObject("Assets/vanaja.tga",100,100,400,400);
	//graphics->init();
	//fileReader->loadFile("Assets/imadethis.txt");

	/*texture loadTGA("Assets/kuva.tga",header);*/

	//sprite = new SpriteObject(200, 200, 200, 200, texture, shader);
	
	//sprite2 = new SpriteObject(400, 400, 200, 200, texture2, shader);


	red = 0;
	blue = 0;
	green = 0;

	initialized = true;
}

void Engine::deInit()
{
	initialized = false;
}

void Engine::update()
{
	red = rand()%2+0.01f;
	blue = rand()%2+0.01f;
	green = rand()%2+0.01f;

	spriteBatch->spriteList[0]->setColor(glm::vec4(red,blue,green,1.f));
	spriteBatch->spriteList[1]->setPosition(rand()%10+500,rand()%10+300);

}

void Engine::draw()
{	
	graphics->clear(1.0f,0.0f,1.0f);

	spriteBatch->draw(viewport);

}