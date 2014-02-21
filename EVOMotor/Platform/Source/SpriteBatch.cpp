#include "Platform/SpriteBatch.h"
#include "Platform/debug.h"

SpriteBatch::SpriteBatch()
{
}

SpriteBatch::~SpriteBatch()
{	
	for(int i = 0; i < spriteList.size(); i++)
	{
		delete spriteList[i];
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
	sprite = new SpriteObject(PosX,PosY,Width,Height,texture,shader);
	spriteList.push_back(sprite);

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
}