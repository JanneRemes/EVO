#include "Include\Background.h"
#include "Platform/debug.h"
#include "Platform/New.h"
#include "Platform/Leak.h"


Background::Background(SpriteBatch* spriteBatch)
	:_spriteBatch(spriteBatch)
{
	
}

Background::~Background()
{
}

void Background::init()
{
	width = Window::winWidth;
	height = Window::winHeight * 1.5f;
	_spriteBatch->addObject("Assets/grassbg.tga",width,height,width,height,0, "grass_1");
	_spriteBatch->addObject("Assets/grassbg.tga",width,height,width/2,height/2,0, "grass_2");
	grass_1	= _spriteBatch->Sprite("grass_1");
	grass_2	= _spriteBatch->Sprite("grass_2");

	posY = 500.f;
	posY2 = posY - Window::winHeight*1.5f;
	posX = Window::winWidth/2;
	posX2 = Window::winWidth/2;
	//posZ = -0.9f;

}
void Background::update(float dt)
{
	if(posY >= Window::winHeight*2)
	{
		posY = posY2 - height;
	}
	if(posY2 >= Window::winHeight*2)
	{
		posY2 = posY - height;
	}

	posY += 500*dt;
	posY2 += 500*dt;
	grass_1->setPosition(Window::winWidth/2,posY);
	grass_2->setPosition(Window::winWidth/2,posY2);
}