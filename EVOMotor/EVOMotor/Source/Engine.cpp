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
	#if defined (WIN32)

	winGame->deInit();
	winGame->~WindowsGame();

	#endif
	#if defined (__ANDROID__)

	androidGame->deInit();

	#endif
}

bool Engine::isInit()
{
	return initialized;
}

void Engine::init()
{
	#if defined (WIN32)

	winGame = new WindowsGame();
	winGame->init();

	#endif
	#if defined (__ANDROID__)

	androidGame= new AndroidGame();
	androidGame->init();

	#endif

	initialized = true;
}

void Engine::deInit()
{
	initialized = false;
}

void Engine::update()
{
	#if defined (WIN32)

	winGame->update();

	#endif
	#if defined (__ANDROID__)

	androidGame->update();

	#endif
}

void Engine::draw()
{	
	#if defined (WIN32)

	winGame->draw();

	#endif
	#if defined (__ANDROID__)

	androidGame->draw();

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