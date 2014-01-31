#ifndef WINDOW_H_
#define WINDOW_H_

#include <stdio.h>
#include <iostream>
#include <string>
#include <stdarg.h>
#include <stdlib.h>
#include <sstream>
#include <fstream>
#include <incl/GL/glew.h>
#include <incl/GLFW/glfw3.h>
//#include <incl/glm/ext.hpp>

class Window
{
public:
	Window(void);
	~Window(void);
	int CreateWindow(int height, int width,const char* name);
	bool isOpen();
	void pollEvents();
	GLFWwindow* window;

private:
};

#endif

