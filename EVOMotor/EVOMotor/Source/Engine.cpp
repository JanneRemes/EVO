#include "Include/Engine.h"
#include "Platform/debug.h"
#include "Platform/New.h"
#include "Platform/Leak.h"
#include "Platform/Rectangle.h"

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
	delete fireball;

	#if defined (WIN32)

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
	fireball =		EVO_NEW Fireball(spriteBatch);

	//Initialize
	spriteBatch->init(shader);
	background =	EVO_NEW Background(spriteBatch);
	//-----
	fireball->init();
	fireball->Add(glm::vec2(100.f,100.f));
	//-----
	background->init();

	//Add starting size and positions to sprite, also filepath and name must be set
	spriteBatch->addObject("Assets/Waluigi.tga",200,200,0,0,10,"waluigi");
	spriteBatch->addObject("Assets/Weegee.tga",200,200,Window::winWidth,Window::winHeight,11,"weegee");

	spriteBatch->addAnimatedObject("Assets/anim.tga",64,64,4,10,12, "animu");
	spriteBatch->addAnimatedObject("Assets/testi.tga",128,128,4,50,13, "knight");
	spriteBatch->addAnimatedObject("Assets/ossi.tga",128,128,2,50,14, "ossi");

	//Set sprites to spriteBatch so we can update and draw them
	waluigi		= spriteBatch->Sprite("waluigi");
	weegee		= spriteBatch->Sprite("weegee");

	praystation = spriteBatch->SpriteAnimation("animu");
	knight		= spriteBatch->SpriteAnimation("knight");
	ossi		= spriteBatch->SpriteAnimation("ossi");

	praystation->setAnimation(1,2,1);
	knight->setAnimation(2,3,4);
	ossi->setAnimation(0,0,1);
	
	//#if defined (WIN32)
	writeLog("before");
	text = spriteBatch->addText("arial.ttf",23.f,1,"testiTeksti");
	writeLog("after");
	text->addText(L"Juokseva haiskore: 100",glm::vec4(1,1,1,1));
	writeLog("sexond");
	text->setPosition(50,200);
	//#endif

	red = 0;
	blue = 0;
	green = 0;

	knightPos.x = Window::winWidth/2;
	knightPos.y = Window::winHeight-Window::winHeight/5;

	targetPos.x = 0;
	targetPos.y = 0;
	targetSpeed = 0;
	touchPosX = 0;
	touchPosY = 0;
	rot = 0;
	initialized = true;

	hand = 1.0f;
	fireRate = 0.f;

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
	//waluigi->setPosition(posX2,posY2);

	weegee->setPosition(Window::winWidth,Window::winHeight);
	//ossi->setPosition(Window::winWidth/2,100);

	fireball->Update(dt);

	//knight->setPosition(350,850);
///////////////////////////////////////////////KNIGHT//
	targetPos= input->getCursorPos();
	const float speedMult = 5.f;
	targetSpeed = speedMult *  abs((targetPos - knightPos).x);

	//knight liikkuu kursorin mukaan
	if(knightPos.x <= targetPos.x)
		knightPos.x += targetSpeed * dt;
	else
		knightPos.x -= targetSpeed * dt;
	knight->setPosition(knightPos.x,knightPos.y);

	if(knight->getPosition().x >= Window::winWidth) //ei saa menn� reunan yli
	{
		knightPos.x=Window::winWidth;
		knight->setPosition(knightPos.x,knightPos.y);
	}
	if(knight->getPosition().x <= 0) //ei saa menn� reunan yli
	{
		knightPos.x=0;
		knight->setPosition(knightPos.x,knightPos.y);
	}

////////////////////////////////////////////////OSSI//
	ossi->setPosition(cosf(1.f+totalTime/2)*Window::winWidth/3 + Window::winWidth/2,
		sinf(1.f+totalTime*2)*Window::winHeight/20+Window::winHeight/6);
	
	background->update(dt);

	//You must update spriteBatch
	spriteBatch->update(dt);

	checkCollision();

	fireRate += dt;
	if(fireRate >= 2)
	{
		fireball->Add(glm::vec2(ossi->getPosition().x-(45.f*hand),ossi->getPosition().y+30.f));
		hand = hand * -1.0f;
		fireRate = 0.f;
	}

}

void Engine::draw()
{	
	//Set graphics and clearcolor
	graphics->clear(0.0f,0.0f,1.0f);

	#if defined (WIN32)

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
		praystation->setSpeed(0.5f);
	}
	else
	{
		praystation->setSpeed(10);
	}

	if(input->MouseButtonPress(evo::buttons::MouseLeft))
	{
		//posX = input->getCursorPos().x;
		//posY = input->getCursorPos().y;
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
		knightPos.x -= 7;
	}

	if(input->keyPress(evo::Keys::D))
	{
		knightPos.x += 7;
	}

	#endif
}

void Engine::checkCollision()
{
	//for(size_t i = 0; i < spriteBatch->spriteList.size(); ++i)
	//{
	//	for(size_t j = i + 1; j < spriteBatch->spriteList.size(); ++j)
	//	{
	//		auto& rect1 = spriteBatch->spriteList[i]->getRect();
	//		auto& rect2 = spriteBatch->spriteList[j]->getRect();
	//		if(rect1.checkCol(rect2))
	//		{
	//			// Do collision related things
	//			writeLog("*ExplosionNoise!*");
	//		}
	//	}
	//}

	if(knight->getRectangle().checkCol(ossi->getRectangle()))
	{
		writeLog("Poks\n");
	}

	for(int i = fireball->Fireballs.size() -1; i >= 0; i--)
	{
		if(knight->getRectangle().checkCol(fireball->Fireballs[i]->getRectangle()))
		{
			fireball->Fireballs[i]->setPosition(fireball->Fireballs[i]->getPosition().x,
												knight->getPosition().y - knight->getRectangle().m_dimensions.y); 
			fireball->Fireballs[i]->setSpeed(fireball->Fireballs[i]->getSpeed()*-1);
			knight->setAnimation(0,2,4);
			writeLog("KIMMOTUSSSSS\n");
		}
		if(knight->_curFrame == 1)
		{	
			knight->setAnimation(2,3,4);
		}
		else
		{}
		/*if(ossi->getRectangle().checkCol(fireball->Fireballs[i]->getRectangle()))
		{
			fireball->Fireballs[i]->setSpeed(fireball->Fireballs[i]->getSpeed()*-1);
			writeLog("KIMMOTUSSSSS\n");
		}*/
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
	targetPos.x = touchPosX;
	//posY = touchPosY;
	//writeLog("Weegee position: [%f, %f]",posX2,posY2);
}

#endif
