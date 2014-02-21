#ifndef DEBUG_H_
#define DEBUG_H_

#include "Platform/Window.h"


static void writeLog(const char* text, ...)
{
	//tekee listan nimeltä v
	va_list v;
	//alustaa v:n arvon ja antaa tekstin
	va_start(v, text);
	//tulostaa listan v sisältämän tekstin
	vprintf(text, v);
	//lopettaa listan v
	va_end(v);
}

//käy koodia läpi, ja tulostaa mahdollisen OpenGL-lauseen errorin
static void checkGLError(const char* op)
{
	for(GLint error = glGetError(); error; error = glGetError())
	{
		writeLog("after %s() glError (0x%x)\n", op, error);
	}
}

//Voidille syötetään GLenum ja syötetään GLenumin sisältämä String ja printataan se
static void printGLString(const char *name, GLenum s) 
{
    const char *v = (const char *) glGetString(s);
    writeLog("GL %s = %s\n", name, v);
}

#endif