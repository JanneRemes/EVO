#ifndef ENGINE_H_
#define ENGINE_H_

#include "Platform/Window.h"
#include "Platform/Graphics.h"
#include "Platform/FileReader.h"
#include "Platform/Texture.h"
#include "Platform/SpriteObject.h"
#include "Platform/Shader.h"

class Engine
{
public:
	Engine(void);
	~Engine(void);
	void init();
	void update();
	void draw(GLFWwindow* window);

	static int windowWidth;
	static int windowHeight;
	static float getTotalTime();

private:
	Graphics* graphics;
	Engine* engine;
	Shader* shader;
	Window* window;
	FileReader* fileReader;
	Texture* texture;
	SpriteObject* sprite;
};

#endif