#ifndef SPRITEBATCH_H_
#define SPRITEBATCH_H_

#include "Platform/SpriteObject.h"
#include "Platform/Texture.h"
#include "Platform/Shader.h"
#include "Platform/Viewport.h"
#include <vector>

class SpriteBatch
{
public:
	SpriteBatch();
	~SpriteBatch();

	void addObject( std::string texFilePath,
					float spriteWidth,
					float spriteHeight,
					float spritePosX,
					float spritePosY );
	void init(Shader* shader);
	void draw(Viewport* viewport);

	SpriteObject* sprite;
	Texture* texture;
	Shader* shader;
	Viewport* viewport;

	std::vector<SpriteObject*> spriteList;

};

#endif