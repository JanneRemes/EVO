#ifndef SPRITEBATCH_H_
#define SPRITEBATCH_H_

#include "Platform/SpriteObject.h"
#include "Platform/SpriteSheetObject.h"
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
	void addAnimatedObject( std::string texFilePath,
					float spriteWidth,
					float spriteHeight,
					int frames,
					int speed);
	void init(Shader* shader);
	void draw(Viewport* viewport);

	SpriteObject* sprite;
	SpriteSheetObject* spriteSheet;
	Texture* texture;
	Shader* shader;
	Viewport* viewport;

	std::vector<SpriteObject*> spriteList;
	std::vector<SpriteSheetObject*> spriteSheetList;

};

#endif