#ifndef ENGINE_H_
#define ENGINE_H_

#include "Platform/Window.h"
#include "Platform/Graphics.h"

class Engine
{
public:
	Engine(void);
	~Engine(void);
	void init();
	void update();
	void draw(GLFWwindow* window);
private:
	Graphics* graphics;
	Engine* engine;
};

#endif