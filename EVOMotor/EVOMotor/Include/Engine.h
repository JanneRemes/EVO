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

#if defined (__ANDROID__)

#include <android/input.h>
#include <android/log.h>
#include <android/looper.h>

#include <Platform/Android/android_native_app_glue.h>

#endif

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

#if defined (__ANDROID__)

	void touchInput(android_app* application);

#endif

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