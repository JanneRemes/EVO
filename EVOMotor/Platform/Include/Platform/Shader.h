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
	Shader(const std::string&, const std::string& fragmentFilePath); // Konstruktori, k‰ytt‰‰ alustusfunktiota
	~Shader(); // Destruktori

	bool init(); // Alustusfunktio, k‰ytt‰‰ createProgram() funktiota
	GLuint getUniformLocation(const char* name) const; // Funktio, joka palauttaa objektin uniform variable:n sijainnin 
	void setUniform(const char* name, float value); // Funktio, jolla voidaan asettaa uniform variable liukulukuna
	void setUniform(const char* name, int value); // Funktio, jolla voidaan asettaa uniform variable kokonaislukuna
	void setUniform(const char* name, const float* matrixData); // Funktio, jolla voidaan asettaa uniform variable 4x4 matriisina
	GLuint program() const; // Palauttaa shader-ohjelman

private:

	GLuint loadShader(GLenum shaderType, const char* source); // Shaderin lataus
	void createProgram(); // Shader-ohjelman luonti

	FileReader fileReader;
	std::string _vertexFilePath;
	std::string _fragmentFilePath;
	GLuint _program;
	GLuint _vertexShader;
	GLuint _fragmentShader;
	bool _inUse;
};

#endif