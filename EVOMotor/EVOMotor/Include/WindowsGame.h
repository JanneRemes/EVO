#ifndef WINDOWSGAME_H_
#define WINDOWSGAME_H_

//Platform includes
#include "Platform/Window.h"
#include "Platform/Graphics.h"
#include "Platform/FileReader.h"
#include "Platform/Texture.h"
#include "Platform/SpriteObject.h"
#include "Platform/SpriteSheetObject.h"
#include "Platform/Shader.h"
#include "Platform/Viewport.h"
#include "Platform/SpriteBatch.h"
#include "Platform/Input.h"
#include "Platform/Text.h"
#include "Include/Game.h"
#include <stdlib.h>
//Game includes
#include "Include/Background.h"

class WindowsGame
{
public:
	WindowsGame(void);
	~WindowsGame(void);

	bool isInit();

	void init();
	void deInit();
	void update();
	void draw();
	void KeyboardInput();

	float touchPosX, touchPosY;

private:
	//Platform objects
	Graphics* graphics;
	Shader* shader;
	FileReader* fileReader;
	SpriteBatch* spriteBatch;
	Viewport* viewport;
	Input* input;
	Text* text;
	//Game objects
	SpriteObject* waluigi;
	SpriteObject* grass;
	SpriteSheetObject* praystation;

	bool initialized;

	float red,blue,green;
	int posX, posY;
	float posX2, posY2;
};

#endif