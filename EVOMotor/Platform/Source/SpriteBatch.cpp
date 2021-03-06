#include "Platform/SpriteBatch.h"
#include "Platform/debug.h"
#include "Platform/New.h"
#include "Platform/Leak.h"
#include <algorithm>

bool sortFunc(Object *A,Object *B);

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
	//for(size_t i = 0; i < spriteSheetList.size(); i++)
	//{
	//	//spriteSheetList.erase(spriteSheetList.begin()+i);
	//	delete spriteSheetList[i];
	//}
}
	
Text* SpriteBatch::addText(	const std::string& fontFilePath,
							float fontSize,
							const int layer,
							const std::string& name)
{
	_obj = EVO_NEW Text(fontFilePath,fontSize);
	_obj->_layer = layer;
	spriteList.push_back(_obj);
	return dynamic_cast<Text*>(_obj);
}
void SpriteBatch::addObject(	const std::string& Path,
								float Width,
								float Height,
								float PosX,
								float PosY,
								const int layer,
								const std::string& name)
{
	texture = Texture::load(Path);
	_obj = EVO_NEW SpriteObject(PosX,PosY,Width,Height,texture,shader,name);
	_obj->_layer = layer;
	spriteList.push_back(_obj);
}

void SpriteBatch::addAnimatedObject(	const std::string& Path,
										float Width,
										float Height,
										int frames,
										int speed,
										const int layer,
										const std::string& name)
{
	texture = Texture::load(Path);
	_obj = EVO_NEW SpriteSheetObject(Width,Height,speed,frames,texture,shader,name);
	_obj->_layer = layer;
	spriteList.push_back(_obj);
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
	////Draw all spriteSheetObjects
	//for(int i = 0; i < spriteSheetList.size(); i++)
	//{
	//	viewport->draw(spriteSheetList[i]);
	//}
}

void SpriteBatch::destroy(const std::string& name)	//Kannattaa jakaa kahdeksi funktioksi
{
	for(int i = 0; i < spriteList.size(); i++)
	{
		if(spriteList[i]->_name == name)
		{
			delete spriteList[i];
			spriteList.erase(spriteList.begin()+i);
			return;	//Palauta, �l� breakkaa, koska joutuu k�ym��n koko funktion l�pi breakin kanssa
		}
	}
	//for(int i = 0; i < spriteSheetList.size(); i++)
	//{
	//	if(spriteSheetList[i]->_name == name)
	//	{
	//		delete spriteSheetList[i];
	//		spriteSheetList.erase(spriteSheetList.begin()+i);
	//		return; //Palauta, �l� breakkaa, koska joutuu k�ym��n koko funktion l�pi breakin kanssa
	//	}
	//}
}
void SpriteBatch::destroy(Object* obj) //Poista tietty spriteobject
{
	for(int i = 0; i < spriteList.size(); i++)
	{
		if(spriteList[i] == obj)
		{
			delete spriteList[i];	//Poistetaan haluttu objekti
			spriteList.erase(spriteList.begin()+i);	//Poistetaan j�sen listasta
			return;
		}
	}
}

void SpriteBatch::update(float dt)
{
	std::sort(spriteList.begin(), spriteList.end(),sortFunc);
	//Update all spriteObjects
	for(auto it = spriteList.begin(); it != spriteList.end(); ++it)
	{
		(*it)->update(dt);
	}
	////Update all spriteSheetObjects
	//for(auto it = spriteSheetList.begin(); it != spriteSheetList.end(); ++it)
	//{
	//	(*it)->update(dt);
	//}
}

Object* SpriteBatch::Obj(const std::string& name)
{
	for(int i = 0; i < spriteList.size(); i++)
	{
		if(spriteList[i]->_name == name)
		{
			return spriteList[i];
		}
	}
}

Text* SpriteBatch::TextObj(const std::string& name)
{
	for(int i = 0; i < spriteList.size(); i++)
	{
		if(spriteList[i]->_name == name)
		{
			assert(spriteList[i]->_type == OBJECT_TYPE::TEXT);
			return static_cast<Text*>(spriteList[i]);
		}
	}
}


SpriteObject* SpriteBatch::Sprite(const std::string& name)
{
	for(int i = 0; i < spriteList.size(); i++)
	{
		if(spriteList[i]->_name == name)
		{
			assert(spriteList[i]->_type == OBJECT_TYPE::SPRITE);
			return static_cast<SpriteObject*>(spriteList[i]);
		}
	}
}

SpriteSheetObject* SpriteBatch::SpriteAnimation(const std::string& name)
{	
	int i = 0;
	for(i = 0; i < spriteList.size(); i++)
	{
		if(spriteList[i]->_name == name)
		{
			assert(spriteList[i]->_type == OBJECT_TYPE::SPRITESHEET);
			return static_cast<SpriteSheetObject*>(spriteList[i]);
		}
	}
}

bool sortFunc(Object *A,Object *B)
{
	return A->_layer<B->_layer;
}


		//spriteList[i]->setScale(Viewport::cameraZoom);
		//spriteList[i]->setPosition(
		//	spriteList[i]->getPosition().x * Viewport::cameraZoom,
		//	spriteList[i]->getPosition().y * Viewport::cameraZoom);