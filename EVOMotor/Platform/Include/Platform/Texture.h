#ifndef TEXTURE_H_
#define TEXTURE_H_

#include "Window.h"

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
	Texture(GLubyte* data,int width,int height,int depth);
	Texture(GLubyte* data);
	~Texture(void);

	static GLubyte* loadTGA(const std::string& fileName, tgaHeader &header);
private:

	void init();

	GLubyte* _data;
	GLuint _textureID;

	int _width;
	int _height;
	int _depth;
};

#endif

