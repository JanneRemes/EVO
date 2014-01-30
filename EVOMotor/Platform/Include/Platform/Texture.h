#ifndef TEXTURE_H_
#define TEXTURE_H_

#include "debug.h"

struct tgaHeader
{
    GLubyte idLength;
    GLubyte colorMapType;
	GLubyte type;
	GLushort width;
	GLushort height;
	GLubyte depth;
	GLubyte descriptor;
};

class Texture
{
public:
	Texture(const char * imagepath);
	~Texture(void);

	static GLubyte* loadTGA(const std::string& fileName, tgaHeader &header);

};

#endif

