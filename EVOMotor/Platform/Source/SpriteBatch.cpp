#include "Platform/SpriteBatch.h"
#include "Platform/debug.h"
#include "Platform/New.h"
#include "Platform/Leak.h"

SpriteBatch::SpriteBatch()
{
}

SpriteBatch::~SpriteBatch()
{	
	for(int i = 0; i < spriteList.size(); i++)
	{
		delete spriteList[i];
	}
	for(int i = 0; i < spriteSheetList.size(); i++)
	{
		delete spriteSheetList[i];
	}
}

void SpriteBatch::addObject(	std::string Path,
								float Width,
								float Height,
								float PosX,
								float PosY )
{
	
	checkGLError("ENNEN!!");
	texture = Texture::load(Path);
	checkGLError("NYT!!");
	sprite = EVO_NEW SpriteObject(PosX,PosY,Width,Height,texture,shader);
	spriteList.push_back(sprite);

}

void SpriteBatch::addAnimatedObject(	std::string Path,
								float Width,
								float Height,
								int frames,
								int speed
)
{
	
	checkGLError("ENNEN!!");
	texture = Texture::load(Path);
	checkGLError("NYT!!");
	spriteSheet = EVO_NEW SpriteSheetObject(Width,Height,speed,frames,texture,shader);
	spriteSheetList.push_back(spriteSheet);

}

void SpriteBatch::init(Shader* s)
{
	shader = s;
}

void SpriteBatch::draw(Viewport* viewport)
{
	for(int i = 0; i < spriteList.size(); i++)
	{
		viewport->draw(spriteList[i]);
	}
	for(int i = 0; i < spriteSheetList.size(); i++)
	{
		viewport->draw(spriteSheetList[i]);
	}
}



		//spriteList[i]->setScale(Viewport::cameraZoom);
		//spriteList[i]->setPosition(
		//	spriteList[i]->getPosition().x * Viewport::cameraZoom,
		//	spriteList[i]->getPosition().y * Viewport::cameraZoom);