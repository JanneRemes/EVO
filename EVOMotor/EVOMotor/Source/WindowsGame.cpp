#include "Include/WindowsGame.h"
#include "Platform/debug.h"
#include "Platform/New.h"
#include "Platform/Leak.h"

#include <iostream>
#include <time.h>

WindowsGame::WindowsGame(void)
{
	initialized = false;
}

WindowsGame::~WindowsGame(void)
{
	delete graphics;
	delete viewport;
	delete spriteBatch;
	delete input;
	delete shader;
	delete text;
}

bool WindowsGame::isInit()
{
	return initialized;
}

void WindowsGame::init()
{
	graphics =		EVO_NEW Graphics(Window::winWidth,Window::winHeight);
	viewport =		EVO_NEW Viewport(Window::winWidth,Window::winHeight);
	spriteBatch =	EVO_NEW SpriteBatch();
	input =			EVO_NEW Input();
	shader =		EVO_NEW Shader("Assets/Shaders/basic.vert", "Assets/Shaders/basic.frag");
	text =			EVO_NEW Text("arial.ttf",44.f,viewport);
	
	spriteBatch->init(shader);

	spriteBatch->addObject("Assets/grass.tga",1000,1000,300,300,"grass");
	grass = spriteBatch->Sprite("grass");

	spriteBatch->addObject("Assets/Waluigi.tga",200,200,0,0,"waluigi");
	waluigi = spriteBatch->Sprite("waluigi");

	spriteBatch->addAnimatedObject("Assets/anim.tga",64,64,4,10, "animu");
	praystation = spriteBatch->SpriteAnimation("animu");
	praystation->setAnimation(1,2,40);
	
	wchar_t *teksti = L"A Quick Brown Fox Jumps Over The Lazy Dog 0123456789";
	text->addText(teksti,glm::vec4(1,1,1,1));
	text->setPosition(0,0);

	red = 0;
	blue = 0;
	green = 0;

	posX = 0;
	posY = 0;

	posX2 = 0;
	posY2 = 0;
	touchPosX = 0;
	touchPosY = 0;
	initialized = true;
}

void WindowsGame::deInit()
{
	initialized = false;
}

void WindowsGame::update()
{
	KeyboardInput();

	red = rand()%2+0.01f;
	blue = rand()%2+0.01f;
	green = rand()%2+0.01f;

	waluigi->setPosition(0,0);

	posY += 10;
	grass->setPosition(300,posY);

	//You must update spriteBatch
	spriteBatch->update(0.1f);

}

void WindowsGame::draw()
{
	graphics->clear(0.0f,0.0f,1.0f);
	//You must draw spriteBatch
	spriteBatch->draw(viewport);

	//Draw text here
	text->draw(viewport->projectionMatrix);
}

void WindowsGame::KeyboardInput()
{
	if(input->keyPress(evo::Keys::Down))
	{
		viewport->moveCamera(0,-5.0f);
	}
	if(input->keyPress(evo::Keys::Up))
	{
		viewport->moveCamera(0,5.0f);
	}
	if(input->keyPress(evo::Keys::Left))
	{
		viewport->moveCamera(5.0f,0);
	}
	if(input->keyPress(evo::Keys::Right))
	{
		viewport->moveCamera(-5.0f,0);
	}
	if(input->keyPress(evo::Keys::Space))
	{
		spriteBatch->spriteSheetList[0]->setSpeed(1);
	}
	else
	{
		spriteBatch->spriteSheetList[0]->setSpeed(10);
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