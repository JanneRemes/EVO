#ifndef ENGINE_H_
#define ENGINE_H_

#include "Platform/Window.h"
#include "Platform/Graphics.h"
#include "Platform/FileReader.h"
#include "Platform/Texture.h"
#include "Platform/SpriteObject.h"
#include "Platform/Shader.h"
#include "Platform/Viewport.h"
#include "Platform/SpriteBatch.h"
#include "Platform/Input.h"

#include <stdlib.h>

class Engine
{
public:
	Engine(void);
	~Engine(void);

	bool isInit();

	void init();
	void deInit();
	void update();
	void draw();
	void KeyboardInput();

	static int windowWidth;
	static int windowHeight;

private:
	Graphics* graphics;
	Engine* engine;
	Shader* shader;
	FileReader* fileReader;
	SpriteBatch* spriteBatch;
	Viewport* viewport;
	Input* input;

	bool initialized;

	float red,blue,green;
	int posX, posY;
	int posX2, posY2;
};

#endif