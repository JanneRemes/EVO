#ifndef GRAPHICS_H_
#define GRAPHICS_H_

#include "Platform/Window.h"
//#include "Platform/debug.h"

class Graphics
{
public:
	Graphics();
	Graphics(int width, int height);
	~Graphics();

	void clear(float r, float g, float b) const;
	void init();

	static int screenWidth;
	static int screenHeight;
	static float aspectRatio;

private:

};

#endif