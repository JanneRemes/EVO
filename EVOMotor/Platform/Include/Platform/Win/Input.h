#ifndef INPUT_H_
#define INPUT_H_

#include <iostream>
#include <Platform/OpenGL.hpp>
#include "Platform/Win/Window.h"
#include "Platform/Win/Keyboard.h"
#include "Platform/Win/Mouse.h"
#include <incl/glm/glm.hpp>

class Input
{
public:
	Input();
	~Input();

	bool isKeyPressed;
	bool isMouseButtonPressed;
	bool MouseButtonPress(int button);
	bool keyPress(int key);
	void Update();
	glm::vec2 getCursorPos();
	double *posX;
	float X,Y;
	double *posY;


private:
	

};
#endif