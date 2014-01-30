#ifndef WINDOW_H_
#define WINDOW_H_

#include <stdio.h>
#include <iostream>
#include <string>
#include <stdarg.h>
#include <incl\GL\glew.h>
#include <incl\GLFW\glfw3.h>

class Window
{
public:
	Window(void);
	~Window(void);
	int CreateWindow(int height, int width,const char* name);
	bool isOpen();
	void pollEvents();
private:
	GLFWwindow* window;
};

#endif


