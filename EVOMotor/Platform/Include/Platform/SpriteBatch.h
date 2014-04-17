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

	void addObject( const std::string& texFilePath,
					float spriteWidth,
					float spriteHeight,
					float spritePosX,
					float spritePosY,
					const std::string& name);
	void addAnimatedObject(const std::string& texFilePath,
					float spriteWidth,
					float spriteHeight,
					int frames,
					int speed,
					const std::string& name);

	void init(Shader* shader);
	void update(float dt);
	void draw(Viewport* viewport);
	void destroy(const std::string& name);
	void destroySpriteObject(SpriteObject*);
	//void destroySpriteSheetObject(SpriteSheetObject*);
	//void destroySpriteSheet(const std::string& name);

	SpriteObject* Sprite(const std::string& name);
	SpriteSheetObject* SpriteAnimation(const std::string& name);

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