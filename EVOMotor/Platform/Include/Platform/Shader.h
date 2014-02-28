#ifndef SHADER_H_
#define SHADER_H_

#include "Platform/FileReader.h"
#include <incl/glm/glm.hpp>
#include <incl/glm/gtx/transform.hpp>
#include <incl/glm/matrix.hpp>
#include <iostream>
#include <Platform/OpenGL.hpp>
#include <string>

class Shader
{
public:
	//Shader();
	Shader(const std::string&, const std::string& fragmentFilePath);
	~Shader();

	bool init();
	GLuint getUniformLocation(const char* name) const;
	void setUniform(const char* name, float value);
	void setUniform(const char* name, int value);
	void setUniform(const char* name, const float* matrixData);
	GLuint program() const;

private:

	GLuint loadShader(GLenum shaderType, const char* source);
	void createProgram();

	FileReader fileReader;
	std::string _vertexFilePath;
	std::string _fragmentFilePath;
	GLuint _program;
	GLuint _vertexShader;
	GLuint _fragmentShader;
	bool _inUse;
};

#endif