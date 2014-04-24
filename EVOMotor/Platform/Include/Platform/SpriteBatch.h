#ifndef SPRITEBATCH_H_
#define SPRITEBATCH_H_

#include "Platform/SpriteObject.h"
#include "Platform/SpriteSheetObject.h"
#include "Platform/Texture.h"
#include "Platform/Shader.h"
#include "Platform/Viewport.h"
#include "Platform/Text.h"
#include <vector>
#include <string>

class SpriteBatch
{
public:
	SpriteBatch();
	~SpriteBatch();
	
	Text* addText(	const std::string& fontFilePath = "arial.ttf",
					float fontSize = 44.f,
					const int layer = 20,
					const std::string& name = "");
	void addObject( const std::string& texFilePath,
					float spriteWidth,
					float spriteHeight,
					float spritePosX,
					float spritePosY,
					const int layer,
					const std::string& name);
	void addAnimatedObject(const std::string& texFilePath,
					float spriteWidth,
					float spriteHeight,
					int frames,
					int speed,
					const int layer,
					const std::string& name);

	void init(Shader* shader);
	void update(float dt);
	void draw(Viewport* viewport);
	void destroy(const std::string& name);
	void destroy(Object* obj);
	//void destroySpriteSheetObject(SpriteSheetObject*);
	//void destroySpriteSheet(const std::string& name);
	
	Object* Obj(const std::string& name);
	Text* TextObj(const std::string& name);
	SpriteObject* Sprite(const std::string& name);
	SpriteSheetObject* SpriteAnimation(const std::string& name);
	
	Object* _obj;
	//SpriteObject* sprite;
	//SpriteSheetObject* spriteSheet;
	//Text* text;
	Texture* texture;
	Shader* shader;
	Viewport* viewport;

	std::vector<Object*> spriteList;
	//std::vector<SpriteSheetObject*> spriteSheetList;

private:

	std::string _name;

};

#endif