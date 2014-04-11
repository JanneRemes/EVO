#ifndef FILEREADER_H_
#define FILEREADER_H_

//#include "Platform/Window.h"
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <Platform/OpenGL.hpp>

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

class FileReader
{
public:
	FileReader();
	FileReader(const std::string& filePath);
	~FileReader(void);

	void open(bool isBinary);
	void seek(int offset, int origin);
	void read(unsigned int count, char* buffer);

	unsigned int length();
	int tell();
	std::string loadFile(const std::string& fileName);
	static GLubyte* loadTGA(const std::string &fileName, tgaHeader &header);

private:

	//FILE* file;
	std::ifstream stream;
	std::string filepath;
	

	unsigned int _length;
};

#endif