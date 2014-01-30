#pragma once
#include <stdio.h>
#include <iostream>
#include <string>
#include <stdarg.h>
#include <incl\GL\glew.h>
#include <incl\GLFW\glfw3.h>

void writeLog(const char* text, ...)
{
	va_list v;
	va_start(v, text);
	vprintf(text, v);
	va_end(v);
}

void checkGLError(const char* op)
{
	for(GLint error = glGetError(); error; error = glGetError())
	{
		writeLog("after /s() glError (0x%x)\n", op, error);
	}
}