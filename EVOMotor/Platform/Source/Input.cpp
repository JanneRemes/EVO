#include "Platform/Input.h"
#include "Platform/debug.h"
#include "Platform/New.h"
#include "Platform/Leak.h"

Input::Input()
{
	isKeyPressed = false;
	isMouseButtonPressed = false;
	posX = EVO_NEW double(0);
	posY = EVO_NEW double(0);
	X = 0;
	Y = 0;
	//glfwSetInputMode(Window::window, GLFW_STICKY_KEYS, 1);
}

Input::~Input()
{
	delete posX;
	delete posY;
}

bool Input::keyPress(int key)
{
#if defined(WIN32)

	if(glfwGetKey(Window::window,key) == GLFW_PRESS/* && isKeyPressed == false*/)
	{
		isKeyPressed = true;
		return true;
	}
	
	while(isKeyPressed)
	{
		if(glfwGetKey(Window::window,key) != GLFW_PRESS/* && isKeyPressed == true*/)
		{
			isKeyPressed = false;
		}

		return false;
	}
	//isKeyPressed = glfwGetKey(Window::window,key) == GLFW_PRESS;
	return false;

#endif
}


bool Input::MouseButtonPress(int button)
{
#if defined(WIN32)

	if(glfwGetMouseButton(Window::window,button) == GLFW_PRESS )
	{
		isMouseButtonPressed = true;
		return true;
	}

	while(isMouseButtonPressed)
	{
		if(glfwGetMouseButton(Window::window,button) != GLFW_PRESS )
		{
			isMouseButtonPressed = false;
		}
		return false;
	}
	return false;

#endif
}

glm::vec2 Input::getCursorPos()
{
#if defined(WIN32)

	glfwGetCursorPos(Window::window, posX, posY);
	int wHeigth, wWidth;
	glfwGetWindowSize(Window::window, &wWidth, &wHeigth);

	Y = wHeigth - *posY;
	X = *posX;
	return glm::vec2(X,Y);

#endif
}

void Input::Update()
{
}