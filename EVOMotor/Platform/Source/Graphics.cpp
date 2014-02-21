#include "Platform/Graphics.h"
#include "Platform/debug.h"

//alustetaan staattiset nollaksi
int Graphics::screenHeight = 0;
int Graphics::screenWidth = 0;
float Graphics::aspectRatio = 0;

//Graphicsin konstruktori laittaa arvoja oikeisiin paikkoihin
Graphics::Graphics(int width, int height)
{
	screenHeight = height;
	screenWidth = width;
	aspectRatio = screenWidth / (float)screenHeight;
	init();
}

Graphics::~Graphics() {}

//
void Graphics::clear(float r, float g, float b) const
{
	// Specify pixel arithmetic
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	checkGLError("glBlendFunc");
	//enabloi GL blendin
	glEnable(GL_BLEND);
	checkGLError("glEnable");
	//define front and back-facing polygons 
	glFrontFace(GL_CCW);
	checkGLError("glFrontFace");
	//Disables the front or back-faced polygons that are culled
	glDisable(GL_CULL_FACE);
	checkGLError("glDisable");
	//Enabloi Depth Testin
	glEnable(GL_DEPTH_TEST);
	checkGLError("GL_DEPTH_TEST");
	//specify the value used for depth buffer comparisons
	glDepthFunc(GL_LEQUAL);
	checkGLError("glDepthFunc");
	//v‰ritt‰‰ taustan
	glClearColor(r,g,b,1.0f);
	checkGLError("glClearColor");
	//clears buffers to present values
	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
	checkGLError("glClear");
}

//delete this shit/android ei toimi t‰m‰n kakan takia
void Graphics::draw(GLFWwindow* window)
{
	//This function swaps the front and back buffers of the specified window
	glfwSwapBuffers(window);
}


void Graphics::init()
{
	//printataan string-tyyppej‰
	printGLString("Version", GL_VERSION);
	printGLString("Vendor", GL_VENDOR);
	printGLString("Renderer", GL_RENDERER);
	printGLString("Extensions", GL_EXTENSIONS);

	//printataan konsoliin screenwidth ja screenheight
	writeLog("screenwidth: %d, screenheight: %d", screenWidth, screenHeight);

	//sets the viewport
	glViewport(0,0,screenWidth,screenHeight);
	checkGLError("glViewport");
}

