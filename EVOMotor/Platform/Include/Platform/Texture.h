/*Texture.h
*
*
*/

#ifndef TEXTURE_H_
#define TEXTURE_H_

#include "Platform/Shader.h"
#include "Platform/FileReader.h"
#include <iostream>
#include <stdarg.h>
#include <stdlib.h>
#include <Platform/OpenGL.hpp>
#include <string>
#include <sstream>
#include <fstream>
#include <iostream>

class Texture
{
public:
	Texture();
	Texture(GLubyte* data,int width,int height,int depth);
	Texture(GLubyte* data);
	~Texture(void);

	//Binds texture to shader
	void bind(Shader* shader);
	//Gets textureID
	GLuint getTextureObject() const;
	//Generates random texture
	static Texture* generateRandom(glm::vec2& size);
	//Loads texture and returns Texture
	static Texture* load(const std::string &fileName);
	//Creates blank texture
	static Texture* generateBlank();
	static Texture* blank;

private:
	void init();

	GLubyte* _data;
	GLuint _textureID;

	int _width;
	int _height;
	int _depth;
};

#endif
