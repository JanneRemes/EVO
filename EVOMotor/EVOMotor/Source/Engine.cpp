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
	//If EVO_NEW or new is called, we must delete them
	delete graphics;
	delete viewport;
	delete spriteBatch;
	delete input;
	delete shader;
	delete background;

	#if defined (WIN32)
	delete text;
	#endif
}

bool Engine::isInit()
{
	return initialized;
}

void Engine::init()
{
	//Initialize platform
	graphics =		EVO_NEW Graphics(Window::winWidth,Window::winHeight);
	viewport =		EVO_NEW Viewport(Window::winWidth,Window::winHeight);
	spriteBatch =	EVO_NEW SpriteBatch();
	input =			EVO_NEW Input();
	shader =		EVO_NEW Shader("Assets/Shaders/basic.vert", "Assets/Shaders/basic.frag");
	//fireball =		EVO_NEW Fireball(spriteBatch);

	//Initialize
	spriteBatch->init(shader);
	background =	EVO_NEW Background(spriteBatch);
	//-----
	//fireball->init();
	//fireball->Add(glm::vec2(100.f,100.f));
	//-----
	background->init();

	//Add starting size and positions to sprite, also filepath and name must be set
	//spriteBatch->addObject("Assets/grass.tga",1000,1000,300,300,"grass");
	spriteBatch->addObject("Assets/Waluigi.tga",200,200,0,0,"waluigi");
	spriteBatch->addObject("Assets/Weegee.tga",200,200,0,0,"weegee");

	spriteBatch->addAnimatedObject("Assets/anim.tga",64,64,4,10, "animu");

	spriteBatch->addAnimatedObject("Assets/testi.tga",128,128,4,50, "knight");
	spriteBatch->addAnimatedObject("Assets/ossi.tga",128,128,2,50, "ossi");
	//spriteBatch->addObject("Assets/fire.tga",16,16,0,0,"fire");

	//Set sprites to spriteBatch so we can update and draw them
	//grass		= spriteBatch->Sprite("grass");
	waluigi		= spriteBatch->Sprite("waluigi");
	weegee		= spriteBatch->Sprite("weegee");
	//fire		= spriteBatch->Sprite("fire");



	praystation = spriteBatch->SpriteAnimation("animu");
	knight		= spriteBatch->SpriteAnimation("knight");
	ossi		= spriteBatch->SpriteAnimation("ossi");

	praystation->setAnimation(1,2,40);

	knight->setAnimation(0,3,40);
	ossi->setAnimation(0,0,40);
	
	#if defined (WIN32)
	text =			EVO_NEW Text("arial.ttf",44.f,viewport);
	wchar_t *teksti = L"A Quick Brown Fox Jumps Over The Lazy Dog 0123456789";
	text->addText(teksti,glm::vec4(1,1,1,1));
	text->setPosition(0,0);
	#endif

	red = 0;
	blue = 0;
	green = 0;

	posX = 350;
	posY = 850;

	posX2 = 0;
	posY2 = 0;
	touchPosX = 0;
	touchPosY = 0;
	rot = 0;
	initialized = true;

	totalTime = 0;
}

void Engine::deInit()
{
	initialized = false;
}

void Engine::update(float dt)
{
	//Update Keyboard input
	KeyboardInput();
#if defined (__ANDROID__)
	touchInput();
#endif
	rot += 1.f;
	totalTime += dt;
	
	//Random color generator
	red = rand()%2+0.01f;
	blue = rand()%2+0.01f;
	green = rand()%2+0.01f;

	//Object updates here
	waluigi->setPosition(posX2,posY2);

	weegee->setPosition(700,980);
	ossi->setPosition(350,100);

	//fireball->Update(dt);

	//knight->setPosition(350,850);

	knight->setPosition(posX,posY);

	if(knight->getPosition().x >= 641)
	{
		posX=640;
		knight->setPosition(posX,posY);
	}
	if(knight->getPosition().x <= 99)
	{
		posX=100;
		knight->setPosition(posX,posY);
	}

	ossi->setPosition(cosf(1.f+totalTime/2)*275+350, sinf(1.f+totalTime*2)*50+150);
	
	//waluigi->setRotationZ(rot);
	background->update(dt);

	//You must update spriteBatch
	spriteBatch->update(dt);

	checkCollision();
}

void Engine::draw()
{	
	//Set graphics and clearcolor
	graphics->clear(0.0f,0.0f,1.0f);

	#if defined (WIN32)
	//Draw text here
	text->draw(viewport->projectionMatrix);
	#endif
	//You must draw spriteBatch
	spriteBatch->draw(viewport);

}

void Engine::KeyboardInput()
{
	#if defined (WIN32)
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
		praystation->setSpeed(1);
	}
	else
	{
		praystation->setSpeed(10);
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
		//posY += 10;
	}

	if(input->keyPress(evo::Keys::W))
	{
		//posY -= 10;
	}

	if(input->keyPress(evo::Keys::A))
	{
		posX -= 7;
	}

	if(input->keyPress(evo::Keys::D))
	{
		posX += 7;
	}
	//-----------------------------------
	if(input->keyPress(evo::Keys::J))
	{
		posX2 -= 7;
	}

	if(input->keyPress(evo::Keys::I))
	{
		posY2 -= 7;
	}
	if(input->keyPress(evo::Keys::K))
	{
		posY2 += 7;
	}
	if(input->keyPress(evo::Keys::L))
	{
		posX2 += 7;
	}
	#endif
}

void Engine::checkCollision()
{
	//for(size_t i = 0; i < spriteBatch->spriteList.size(); ++i)
	//{
	//	for(size_t j = i + 1; j < spriteBatch->spriteList.size(); ++j)
	//	{
	//		auto& rect1 = spriteBatch->spriteList[i]->getRectangle();
	//		auto& rect2 = spriteBatch->spriteList[j]->getRectangle();
	//		if(rect1.checkCol(rect2))
	//		{
	//			// Do collision related things
	//			writeLog("*ExplosionNoise!*");
	//		}
	//	}
	//}

	if(weegee->getRectangle().checkCol(waluigi->getRectangle()))
	{
		writeLog("Poks\n");
	}
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
