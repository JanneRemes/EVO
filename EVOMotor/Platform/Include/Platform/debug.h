#ifndef DEBUG_H_
#define DEBUG_H_
#include "Platform/Window.h"

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

static void printGLString(const char *name, GLenum s) 
{
    const char *v = (const char *) glGetString(s);
    writeLog("GL %s = %s\n", name, v);
}

#endif