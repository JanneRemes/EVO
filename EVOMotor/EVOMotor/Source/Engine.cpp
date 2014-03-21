#include "Include/Engine.h"
#include "Platform/debug.h"
#include "Platform/New.h"
#include "Platform/Leak.h"

#include <iostream>
#include <time.h>


int Engine::windowWidth =  0;
int Engine::windowHeight = 0;

Engine::Engine(void)
{
	initialized = false;
}

Engine::~Engine(void)
{
	delete input;
	delete spriteBatch;
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
	graphics = EVO_NEW Graphics(Window::winWidth,Window::winHeight);
	viewport = EVO_NEW Viewport(Window::winWidth,Window::winHeight);
	spriteBatch = EVO_NEW SpriteBatch();
	input = EVO_NEW Input();
	shader = EVO_NEW Shader("Assets/Shaders/basic.vert", "Assets/Shaders/basic.frag");
	
	spriteBatch->init(shader);
	spriteBatch->addObject("Assets/Waluigi.tga",200,200,0,0);
	spriteBatch->addObject("Assets/Weegee.tga",170,170,0,0);

	red = 0;
	blue = 0;
	green = 0;

	posX = 0;
	posY = 0;

	posX2 = 0;
	posY2 = 0;
	initialized = true;
}

void Engine::deInit()
{
	initialized = false;
}

void Engine::update()
{
	KeyboardInput();

	red = rand()%2+0.01f;
	blue = rand()%2+0.01f;
	green = rand()%2+0.01f;

	//spriteBatch->spriteList[0]->setColor(glm::vec4(red,blue,green,1.f));
	//spriteBatch->spriteList[1]->setPosition(rand()%10+500+posX2,rand()%10+300+posY2);

	//spriteBatch->spriteList[1]->setColor(glm::vec4(red,blue,green,1.f));
	//spriteBatch->spriteList[0]->setPosition((rand()%10+100)+posX,(rand()%10+100)+posY);

	spriteBatch->spriteList[0]->setPosition(posX,posY);
	spriteBatch->spriteList[1]->setPosition(posX2,posY2);
}

void Engine::draw()
{	
	graphics->clear(0.0f,0.0f,0.0f);

	spriteBatch->draw(viewport);
}

void Engine::KeyboardInput()
{
	if(input->keyPress(evo::Keys::Down))
	{
		viewport->moveCamera(0,5.01f);
	}
	if(input->keyPress(evo::Keys::Up))
	{
		viewport->moveCamera(0,-5.01f);
	}
	if(input->keyPress(evo::Keys::Left))
	{
		viewport->moveCamera(5.01f,0);
	}
	if(input->keyPress(evo::Keys::Right))
	{
		viewport->moveCamera(-5.01f,0);
	}

	if(input->MouseButtonPress(evo::buttons::MouseLeft))
	{
		posX = input->getCursorPos().x;
		posY = input->getCursorPos().y;
	}

	if(input->MouseButtonPress(evo::buttons::MouseRight))
	{
		writeLog("mouse right");
	}

	if(input->MouseButtonPress(evo::buttons::MouseMiddle))
	{
		writeLog("mouse middle");
	}

	if(input->keyPress(evo::Keys::S))
	{
		posY2 -= 10;
	}
	if(input->keyPress(evo::Keys::W))
	{
		posY2 += 10;
	}
	if(input->keyPress(evo::Keys::A))
	{
		posX2 -= 10;
	}
	if(input->keyPress(evo::Keys::D))
	{
		posX2 += 10;
	}
}