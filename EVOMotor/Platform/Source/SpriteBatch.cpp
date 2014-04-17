#include "Platform/SpriteBatch.h"
#include "Platform/debug.h"
#include "Platform/New.h"
#include "Platform/Leak.h"

SpriteBatch::SpriteBatch()
{
}

SpriteBatch::~SpriteBatch()
{	
	for(size_t i = 0; i < spriteList.size(); i++)
	{
		//spriteList.erase(spriteList.begin()+i);
		delete spriteList[i];
	}
	for(size_t i = 0; i < spriteSheetList.size(); i++)
	{
		//spriteSheetList.erase(spriteSheetList.begin()+i);
		delete spriteSheetList[i];
	}
}

void SpriteBatch::addObject(	const std::string& Path,
								float Width,
								float Height,
								float PosX,
								float PosY,
								const std::string& name)
{
	
	checkGLError("ENNEN!!");
	texture = Texture::load(Path);
	checkGLError("NYT!!");
	sprite = EVO_NEW SpriteObject(PosX,PosY,Width,Height,texture,shader,name);
	spriteList.push_back(sprite);

}

void SpriteBatch::addAnimatedObject(	const std::string& Path,
										float Width,
										float Height,
										int frames,
										int speed,
										const std::string& name)
{
	
	checkGLError("ENNEN!!");
	texture = Texture::load(Path);
	checkGLError("NYT!!");
	spriteSheet = EVO_NEW SpriteSheetObject(Width,Height,speed,frames,texture,shader,name);
	spriteSheetList.push_back(spriteSheet);

}

void SpriteBatch::init(Shader* s)
{
	shader = s;
}

void SpriteBatch::draw(Viewport* viewport)
{
	//Draw all spriteObjects
	for(int i = 0; i < spriteList.size(); i++)
	{
		viewport->draw(spriteList[i]);
	}
	//Draw all spriteSheetObjects
	for(int i = 0; i < spriteSheetList.size(); i++)
	{
		viewport->draw(spriteSheetList[i]);
	}
}

void SpriteBatch::destroy(const std::string& name)	//Kannattaa jakaa kahdeksi funktioksi
{
	for(int i = 0; i < spriteList.size(); i++)
	{
		if(spriteList[i]->_name == name)
		{
			delete spriteList[i];
			spriteList.erase(spriteList.begin()+i);
			return;	//Palauta, ‰l‰ breakkaa, koska joutuu k‰ym‰‰n koko funktion l‰pi breakin kanssa
		}
	}
	
	for(int i = 0; i < spriteSheetList.size(); i++)
	{
		if(spriteSheetList[i]->_name == name)
		{
			delete spriteSheetList[i];
			spriteSheetList.erase(spriteSheetList.begin()+i);
			return; //Palauta, ‰l‰ breakkaa, koska joutuu k‰ym‰‰n koko funktion l‰pi breakin kanssa
		}
	}
}
void SpriteBatch::destroySpriteObject(SpriteObject* spriteObject) //Poista tietty spriteobject
{
	for(int i = 0; i < spriteList.size(); i++)
	{
		if(spriteList[i] == spriteObject)	
		{
			delete spriteList[i];	//Poistetaan haluttu objekti
			spriteList.erase(spriteList.begin()+i);	//Poistetaan j‰sen listasta
			return;
		}
	}
	
}

void SpriteBatch::update(float dt)
{
	//Update all spriteObjects
	for(auto it = spriteList.begin(); it != spriteList.end(); ++it)
	{
		(*it)->update(dt);
	}
	//Update all spriteSheetObjects
	for(auto it = spriteSheetList.begin(); it != spriteSheetList.end(); ++it)
	{
		//spriteSheetList[i]->update(dt);
		(*it)->update(dt);
	}
}

SpriteObject* SpriteBatch::Sprite(const std::string& name)
{
	int i = 0;
	for(i = 0; i < spriteList.size(); i++)
	{
		if(spriteList[i]->_name == name)
		{
			return spriteList[i];
		}
	}
}

SpriteSheetObject* SpriteBatch::SpriteAnimation(const std::string& name)
{	
	int i = 0;
	for(i = 0; i < spriteSheetList.size(); i++)
	{
		if(spriteSheetList[i]->_name == name)
		{
			return spriteSheetList[i];
		}
	}
}

		//spriteList[i]->setScale(Viewport::cameraZoom);
		//spriteList[i]->setPosition(
		//	spriteList[i]->getPosition().x * Viewport::cameraZoom,
		//	spriteList[i]->getPosition().y * Viewport::cameraZoom);