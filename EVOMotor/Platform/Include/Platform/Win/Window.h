#ifndef WINDOW_H_
#define WINDOW_H_

#include <iostream>
#include <Platform/OpenGL.hpp>
#include <string>
#include <stdarg.h>
#include <stdlib.h>
#include <incl/glm/glm.hpp>

class Window
{
public:
	Window(void);
	~Window(void);
	int createWindow(int height, int width, const char* name);
	bool isOpen();
	void pollEvents();
	static GLFWwindow* window;
	void SwapBuffers();
	int wHeigth, wWidth;
	glm::vec2 getWindowSize();
	static void window_size_callback(GLFWwindow* window, int width, int height);
	static int winHeight;
	static int winWidth;

	void PositionCheck(int, int);

private:
};

#endif