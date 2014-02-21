#ifndef GRAPHICS_H_
#define GRAPHICS_H_

#include "Platform/Window.h"

class Graphics
{
	//annetaan/alustetaan arvoja/muuttujia
public:
	Graphics(int width, int height);
	~Graphics();

	void clear(float r, float g, float b) const;
	void init();
	//void draw(GLFWwindow* window);

	static int screenWidth;
	static int screenHeight;
	static float aspectRatio;

private:

};

#endif