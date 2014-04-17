#include "Include/Fireball.h"

Fireball::Fireball(SpriteBatch* spriteBatch)
	: fireball(nullptr)
{
	_spriteBatch = spriteBatch;

	x   = 0;
	y   = 0;
	ID  = 0;
}

Fireball::~Fireball()
{

}

void Fireball::init()
{
	
}

void Fireball::Add(glm::vec2 position)
{
	_spriteBatch->addObject("Assets/fire.tga",16,16,500,500, "fire" + std::to_string((long double)ID));
	fireball = _spriteBatch->Sprite("fire" + std::to_string((long double)ID));
	Fireballs.push_back(fireball);
	++ID;

}

void Fireball::Update(float dt)
{
	for(int i = Fireballs.size() -1; i >= 0; i--)
	{
		x += Fireballs[i]->getPosition().x;
		y += Fireballs[i]->getPosition().y + 50;
		Fireballs[i]->setPosition(x,y);

		if(Fireballs[i]->getPosition().y >= 1050.f)
		{
			_spriteBatch->destroySpriteObject(Fireballs[i]);
			Fireballs.erase(Fireballs.begin()+i);
		}
	}
}
