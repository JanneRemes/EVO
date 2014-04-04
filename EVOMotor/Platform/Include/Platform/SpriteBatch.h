#ifndef SPRITEBATCH_H_
#define SPRITEBATCH_H_

#include "Platform/SpriteObject.h"
#include "Platform/SpriteSheetObject.h"
#include "Platform/Texture.h"
#include "Platform/Shader.h"
#include "Platform/Viewport.h"
#include <vector>
#include <string>

class SpriteBatch
{
public:
	SpriteBatch();
	~SpriteBatch();

	void addObject( std::string texFilePath,
					float spriteWidth,
					float spriteHeight,
					float spritePosX,
					float spritePosY,
					std::string name);
	void addAnimatedObject( std::string texFilePath,
					float spriteWidth,
					float spriteHeight,
					int frames,
					int speed,
					std::string name);
	void init(Shader* shader);
	void update(float dt);
	void draw(Viewport* viewport);
	SpriteObject* Sprite(std::string name);
	SpriteSheetObject* SpriteAnimation(std::string name);

	SpriteObject* sprite;
	SpriteSheetObject* spriteSheet;
	Texture* texture;
	Shader* shader;
	Viewport* viewport;


	std::vector<SpriteObject*> spriteList;
	std::vector<SpriteSheetObject*> spriteSheetList;

private:

	std::string _name;

};

#endif