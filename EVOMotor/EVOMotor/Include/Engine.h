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

class Engine
{
public:
	Engine(void);
	~Engine(void);
	void init();
	void update();
	void draw();

	static int windowWidth;
	static int windowHeight;
	static float getTotalTime();

private:
	Graphics* graphics;
	Engine* engine;
	Shader* shader;
	FileReader* fileReader;
	SpriteBatch* spriteBatch;
	Viewport* viewport;

	float red,blue,green;
};

#endif