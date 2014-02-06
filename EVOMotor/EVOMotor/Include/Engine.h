#ifndef ENGINE_H_
#define ENGINE_H_

#include "Platform/Window.h"
#include "Platform/Graphics.h"
#include "Platform/FileReader.h"
#include "Platform/Texture.h"

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

private:
	Graphics* graphics;
	Engine* engine;
	Window* window;
	FileReader* fileReader;
	Texture* texture;
};

#endif