#ifndef MOUSE_H_
#define MOUSE_H_

#include "Platform/OpenGL.hpp"

namespace evo
{
	enum buttons
	{
		MouseLeft = GLFW_MOUSE_BUTTON_LEFT,
		MouseRight = GLFW_MOUSE_BUTTON_RIGHT,
		/*MouseWheelUp = 
		MouseWheelDown = FIX IT LATER */
		MouseMiddle = GLFW_MOUSE_BUTTON_MIDDLE
	
	};
}
#endif