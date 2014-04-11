#ifndef FIREBALL_H_
#define FIREBALL_H_

#include <iostream>
#include <Platform/OpenGL.hpp>
#include <string>
#include <stdlib.h>
#include <incl/glm/glm.hpp>
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
	void Delete(SpriteObject*,int);
	std::vector <SpriteObject*> Fireballs;

	float x,y;
	int ID;

	SpriteObject* fireball;
	SpriteBatch* _spriteBatch;
};

#endif