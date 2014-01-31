#include "Platform/Graphics.h"

int Graphics::screenHeight = 0;
int Graphics::screenWidth = 0;
float Graphics::aspectRatio = 0;

Graphics::Graphics(int width, int height)
{
	screenHeight = height;
	screenWidth = width;
	aspectRatio = screenWidth / (float)screenHeight;
	init();
}

Graphics::~Graphics() {}

void Graphics::clear(float r, float g, float b) const
{
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	//checkGLError
	glEnable(GL_BLEND);
	//checkGLError

	glFrontFace(GL_CCW);
	//checkGLError
	//glEnable(GL_CULL_FACE);
	glDisable(GL_CULL_FACE);
	//glEnable(GL_CULL_FACE);

	glEnable(GL_DEPTH_TEST);
	//checkGLError
	glDepthFunc(GL_LEQUAL);
	//checkGLError

	glClearColor(r,g,b,1.0f);
	//checkGLError
	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
	//checkGLError
}

void Graphics::init()
{
	//printGLString("Version", GL_VERSION);
	//printGLString("Vendor", GL_VENDOR);
	//printGLString("Renderer", GL_RENDER);
	//printGLString("Extensions", GL_EXTENSIONS);

	//writeLog("screenwidth:%d, screenheight:%d", screenWidth, screenHeight);
	glViewport(0,0,screenWidth,screenHeight);
	//checkglerror
}