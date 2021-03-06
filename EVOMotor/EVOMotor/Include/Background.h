#ifndef BACKGROUND_H_
#define BACKGROUND_H_

#include "Platform/Window.h"
#include "Platform/Graphics.h"
#include "Platform/FileReader.h"
#include "Platform/Texture.h"
#include "Platform/SpriteObject.h"
#include "Platform/SpriteSheetObject.h"
#include "Platform/SpriteBatch.h"

class Background
{
public:
	Background(SpriteBatch*);
	~Background();

	void init();
	void update(float dt);

	SpriteObject* grass_1;
	SpriteObject* grass_2;
	SpriteBatch* _spriteBatch;

	float posX, posY, posY2, posX2;
	float width,height;

private:

};

#endif