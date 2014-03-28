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
	delete graphics;
	delete viewport;
	delete spriteBatch;
	delete input;
	delete shader;
}

bool Engine::isInit()
{
	return initialized;
}

void Engine::init()
{
	graphics =		EVO_NEW Graphics(Window::winWidth,Window::winHeight);
	viewport =		EVO_NEW Viewport(Window::winWidth,Window::winHeight);
	spriteBatch =	EVO_NEW SpriteBatch();
	input =			EVO_NEW Input();
	shader =		EVO_NEW Shader("Assets/Shaders/basic.vert", "Assets/Shaders/basic.frag");
	text =			EVO_NEW Text("arial.ttf",20.f,viewport);
	
	spriteBatch->init(shader);
	spriteBatch->addObject("Assets/Waluigi.tga",200,200,0,0);
	spriteBatch->addObject("Assets/Weegee.tga",170,170,0,0);

	wchar_t *teksti = L"A Quick Brown Fox Jumps Over The Lazy Dog 0123456789";
	text->addText(teksti,glm::vec4(1,1,1,1));

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
	spriteBatch->spriteList[1]->setPosition(posX2,posY2);

	//spriteBatch->spriteList[1]->setColor(glm::vec4(red,blue,green,1.f));
	//spriteBatch->spriteList[0]->setPosition((rand()%10+100)+posX,(rand()%10+100)+posY);

	spriteBatch->spriteList[0]->setPosition(posX,posY);
	//spriteBatch->spriteList[1]->setPosition(posX2,posY2);
}

void Engine::draw()
{	
	graphics->clear(0.0f,0.0f,0.0f);
	text->draw(viewport->projectionMatrix);
	spriteBatch->draw(viewport);
}

void Engine::KeyboardInput()
{
	#if defined(WIN32)
	if(input->keyPress(evo::Keys::Down))
	{
		viewport->moveCamera(0,5.0f);
	}
	if(input->keyPress(evo::Keys::Up))
	{
		viewport->moveCamera(0,-5.0f);
	}
	if(input->keyPress(evo::Keys::Left))
	{
		viewport->moveCamera(5.0f,0);
	}
	if(input->keyPress(evo::Keys::Right))
	{
		viewport->moveCamera(-5.0f,0);
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
	#endif
}

#if defined (__ANDROID__)

int32_t Engine::processTouchInput(AInputEvent* ev)
{
	const int32_t action = AMotionEvent_getAction(ev);
	int32_t index;
	
	switch(action & AMOTION_EVENT_ACTION_MASK)
	{
		case AMOTION_EVENT_ACTION_DOWN:
		case AMOTION_EVENT_ACTION_POINTER_DOWN:
		index = (action & AMOTION_EVENT_ACTION_POINTER_INDEX_MASK)
			>> AMOTION_EVENT_ACTION_POINTER_INDEX_SHIFT;
		touchPosX = AMotionEvent_getX(ev, index);
		touchPosY = AMotionEvent_getY(ev, index);
		
		break;

	case AMOTION_EVENT_ACTION_MOVE:
		{
			const int32_t touchCount = AMotionEvent_getPointerCount(ev);
			for(int32_t i = 0; i < touchCount; ++i)
			{
				touchPosX = AMotionEvent_getX(ev, i);
				touchPosY = AMotionEvent_getY(ev, i);
				writeLog("Finger position: [%f, %f]",touchPosX,touchPosY);
			}
		}
		break;

	case AMOTION_EVENT_ACTION_UP:
		index = (action & AMOTION_EVENT_ACTION_POINTER_INDEX_MASK)
			>> AMOTION_EVENT_ACTION_POINTER_INDEX_SHIFT;
		touchPosX = AMotionEvent_getX(ev, index);
		touchPosY = AMotionEvent_getY(ev, index);
		break;

	default:
		break;
	}

	return 1;
}

int32_t Engine::processKeyInput(AInputEvent* ev)
{
	const int32_t keyCode = AKeyEvent_getKeyCode(ev);
	const int32_t keyState = AKeyEvent_getAction(ev);
	return 0;
}

void Engine::touchInput()
{
	posX2 = touchPosX;
	posY2 = touchPosY;
	//writeLog("Weegee position: [%f, %f]",posX2,posY2);
}

#endif