#include "Platform/Shader.h"
#include "Platform/debug.h"

//Shader::Shader()
//{
//}

Shader::Shader(const std::string& vertexFilePath, const std::string& fragmentFilePath):
	_program(0),
	_vertexShader(0),
	_fragmentShader(0),
	_vertexFilePath(vertexFilePath),
	_fragmentFilePath(fragmentFilePath),
	_inUse(false),
	fileReader("string")
{
	init();
}

Shader::~Shader()
{
}

bool Shader::init() 
{
	createProgram();
	return true;
}

GLuint Shader::getUniformLocation(const char* name) const
{
	glUseProgram(_program);
	checkGLError("glUseProgram");
	GLuint location = glGetUniformLocation(_program, name);
	checkGLError("glGetUniformLocation");
	return location;
}

void Shader::setUniform(const char* name, float value)
{
	glUniform1f(getUniformLocation(name), value);
	checkGLError("glUniform1f");
}

void Shader::setUniform(const char* name, int value)
{
	glUniform1i(getUniformLocation(name), value);
	checkGLError("glUniform1i");
}

void Shader::setUniform(const char* name, const float* matrixData)
{
	glUniformMatrix4fv(getUniformLocation(name), 1, GL_FALSE, matrixData);
	checkGLError("glUniformMatrix4fv");
}

GLuint Shader::program() const
{
	return _program;
}

GLuint Shader::loadShader(GLenum shaderType, const char* source)
{
	checkGLError("mika on vika!");
	GLuint shader = glCreateShader(shaderType);
	if (shader)
	{
		glShaderSource(shader, 1, &source, NULL);
		checkGLError("glShaderSource");
		glCompileShader(shader);
		checkGLError("glCompileShader");
		GLint compiled = 0;
		glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);
		if (!compiled)
		{
			GLint infoLen = 0;
			glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLen);
			if (infoLen)
			{
				char* buf = (char*) malloc(infoLen);
				if (buf)
				{
					glGetShaderInfoLog(shader, infoLen, NULL, buf);
					writeLog("Could not compile shader %d: \n%s \n", shaderType, buf);
					free(buf);
				}
				glDeleteShader(shader);
				checkGLError("glDeleteShader");
				shader = 0;
			}
		}
	}
	return shader;
}

void Shader::createProgram()
{
	//////////////////FIX LOADFILE
	_vertexShader = loadShader(GL_VERTEX_SHADER,  fileReader.loadFile(_vertexFilePath).c_str());
	if (!_vertexShader)
	{
		writeLog("Vertexshader failed");
		return;
	}
	
	_fragmentShader = loadShader(GL_FRAGMENT_SHADER,  fileReader.loadFile(_fragmentFilePath).c_str());
	if (!_fragmentShader)
	{
		writeLog("Fragmentshader failed");
		return;
	}

	_program = glCreateProgram();
	checkGLError("glCreateProgram");

	if (_program)
	{
		glAttachShader(_program, _vertexShader);
		checkGLError("glAttachShader");
		glAttachShader(_program, _fragmentShader);
		checkGLError("glAttachShader");

		glLinkProgram(_program);
		checkGLError("glLinkProgram");
		GLint linkStatus = GL_FALSE;

		glGetProgramiv(_program, GL_LINK_STATUS, &linkStatus);

		if (linkStatus != GL_TRUE)
		{
			writeLog("Program link failed");
			GLint bufLength = 0;
			glGetProgramiv(_program, GL_INFO_LOG_LENGTH, &bufLength);
			if (bufLength)
			{
				char* buf = (char*) malloc(bufLength);
				if (buf)
				{
					glGetProgramInfoLog(_program, bufLength, NULL, buf);
					writeLog("Could not link program:\n%s", buf);
					free(buf);
				}
			}
			glDeleteProgram(_program);
			_program = 0;
		}
	}
}