#include "Platform/Graphics.h"
#include "Platform/debug.h"

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
	checkGLError("glBlendFunc");
	glEnable(GL_BLEND);
	checkGLError("glEnable");
	glFrontFace(GL_CCW);
	checkGLError("glFrontFace");

	glDisable(GL_CULL_FACE);
	checkGLError("glDisable");

	glEnable(GL_DEPTH_TEST);
	checkGLError("GL_DEPTH_TEST");
	glDepthFunc(GL_LEQUAL);
	checkGLError("glDepthFunc");

	glClearColor(r,g,b,1.0f);
	checkGLError("glClearColor");
	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
	checkGLError("glClear");
}

void Graphics::draw(GLFWwindow* window)
{
	glfwSwapBuffers(window);
}

void Graphics::init()
{
	printGLString("Version", GL_VERSION);
	printGLString("Vendor", GL_VENDOR);
	printGLString("Renderer", GL_RENDER);
	printGLString("Extensions", GL_EXTENSIONS);

	writeLog("screenwidth: %d, screenheight: %d", screenWidth, screenHeight);
	glViewport(0,0,screenWidth,screenHeight);
	checkGLError("glViewport");
}

