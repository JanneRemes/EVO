#include "Include/Fireball.h"

Fireball::Fireball(SpriteBatch* spriteBatch)
	: fireball(nullptr)
{
	_spriteBatch = spriteBatch;
}

Fireball::~Fireball()
{

}

void Fireball::init()
{
	x   = 0;
	y   = 0;
	ID  = 0;
}

void Fireball::Add(glm::vec2 position)
{
	++ID;
	_spriteBatch->addObject("Assets/fire.tga",16,16,500,500, "fire" + std::to_string((long double)ID));
	fireball = _spriteBatch->Sprite("fire" + std::to_string((long double)ID));
	Fireballs.push_back(fireball);

}

void Fireball::Update(float dt)
{
	for(int i = 0; i < Fireballs.size(); i++)
	{
		x += Fireballs[i]->getPosition().x;
		y += Fireballs[i]->getPosition().y + 50;
		Fireballs[i]->setPosition(x,y);

		if(Fireballs[i]->getPosition().y >= 1050.f)
			Delete(Fireballs[i],i);
	}
}

void Fireball::Delete(SpriteObject* _fireball,int id)
{
	_spriteBatch->destroy("fire" + std::to_string((long double)id));
	if(_fireball != nullptr)
		delete _fireball;
}