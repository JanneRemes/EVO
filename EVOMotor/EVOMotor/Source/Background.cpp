#include "Include\Background.h"
#include "Platform/debug.h"
#include "Platform/New.h"
#include "Platform/Leak.h"


Background::Background(SpriteBatch* spriteBatch)
{
	_spriteBatch = spriteBatch;
}

Background::~Background()
{
}

void Background::init()
{
	_spriteBatch->addObject("Assets/grass.tga",1000,1000,500,500, "grass_1");
	_spriteBatch->addObject("Assets/grass.tga",1000,1000,500,500, "grass_2");
	grass_1	= _spriteBatch->Sprite("grass_1");
	grass_2	= _spriteBatch->Sprite("grass_2");

	posY = 500.f;
	posY2 = posY - 1000.f;
	posX = 500.f;
	posX2 = 500.f;

}
void Background::update(float dt)
{
	if(posY >= 1500)
	{
		posY = posY2 - 1000.f;
	}
	if(posY2 >= 1500)
	{
		posY2 = posY - 1000.f;
	}

	posY += 20;
	posY2 += 20;
	grass_1->setPosition(500,posY);
	grass_2->setPosition(500,posY2);
}