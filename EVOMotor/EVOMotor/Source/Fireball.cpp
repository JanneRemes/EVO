#include "Include/Fireball.h"
#include "Platform/debug.h"
#include "Platform/New.h"
#include "Platform/Leak.h"
#include "Platform/Window.h"
#include <string>
#include <sstream>

template <typename T>
std::string to_string(T value)
{
    std::ostringstream os ;
    os << value ;
    return os.str() ;
}

Fireball::Fireball(SpriteBatch* spriteBatch)
	: fireball(nullptr)
{
	_spriteBatch = spriteBatch;

	x   = 0;
	y   = 0;
	ID  = 0;
	movement = 0;
	totalTime = 0;
	
}

Fireball::~Fireball()
{
	
}

void Fireball::init()
{
	//_texture = Texture::load("Assets/fire.tga");
}

void Fireball::Add(glm::vec2 position)
{
	_spriteBatch->addObject("Assets/fire.tga",16,16,position.x,position.y,20, "fire" + to_string(ID));
	fireball = _spriteBatch->Sprite("fire" + to_string(ID));
	Fireballs.push_back(fireball);
	fireball->setSpeed(500.f);
	++ID;
}

void Fireball::Update(float dt)
{
	totalTime += dt;
	for(int i = Fireballs.size() -1; i >= 0; i--)
	{
		y = Fireballs[i]->getPosition().y + Fireballs[i]->getSpeed()*dt;
		x = Fireballs[i]->getPosition().x+cosf(1.f+totalTime*10)*6;
		Fireballs[i]->setPosition(x,y);

		if(Fireballs[i]->getPosition().y >= Window::winHeight || Fireballs[i]->getPosition().y <= 0)
		{
			_spriteBatch->destroy(Fireballs[i]);
			Fireballs.erase(Fireballs.begin()+i);
			//movement = 0;
		}
	}
}