/* Window.h (Win32)
** Creates and handles Win32 window 
** 
**
*/
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

//Creates window. Takes height,width and window's title as parameters 
	int createWindow(int height, int width, const char* name);
//Calls glfwSwapBuffer()
	void SwapBuffers();
//Check if window is open
	bool isOpen();
//Calls glfwPollEvents()
	void pollEvents();
//Get window's size as vector2D
	glm::vec2 getWindowSize();
//Callback function when window size is changed
	static void window_size_callback(GLFWwindow* window, int width, int height);

	static GLFWwindow* window;
	int wHeigth;
	int wWidth;
	static int winHeight;
	static int winWidth;


private:
};

#endif