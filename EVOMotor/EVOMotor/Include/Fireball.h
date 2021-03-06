#ifndef FIREBALL_H_
#define FIREBALL_H_

#include <iostream>
#include <Platform/OpenGL.hpp>
#include <string>
#include <stdlib.h>
#include <incl/glm/glm.hpp>
#include <Platform/Texture.h>
#include <Platform/SpriteObject.h>
#include <Platform/SpriteBatch.h>

class Fireball
{
public:
	Fireball(SpriteBatch*);
	~Fireball();
	void init();
	void Add(glm::vec2 position);
	void Update(float dt);
//	void Delete(SpriteObject*); Turha funktio, voidaan poistaa spritebatchin avulla
	std::vector <SpriteObject*> Fireballs;

	float x,y,movement,totalTime;
	int ID;

	SpriteObject* fireball;
	Texture* _texture;
	SpriteBatch* _spriteBatch;
};

#endif