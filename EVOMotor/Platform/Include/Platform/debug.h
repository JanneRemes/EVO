#ifndef DEBUG_H_
#define DEBUG_H_

#include "Platform/Window.h"


static void writeLog(const char* text, ...)
{
	//tekee listan nimelt� v
	va_list v;
	//alustaa v:n arvon ja antaa tekstin
	va_start(v, text);
	//tulostaa listan v sis�lt�m�n tekstin
	vprintf(text, v);
	//lopettaa listan v
	va_end(v);
}

//k�y koodia l�pi, ja tulostaa mahdollisen OpenGL-lauseen errorin
static void checkGLError(const char* op)
{
	for(GLint error = glGetError(); error; error = glGetError())
	{
		writeLog("after %s() glError (0x%x)\n", op, error);
	}
}

//Voidille sy�tet��n GLenum ja sy�tet��n GLenumin sis�lt�m� String ja printataan se
static void printGLString(const char *name, GLenum s) 
{
    const char *v = (const char *) glGetString(s);
    writeLog("GL %s = %s\n", name, v);
}

#endif