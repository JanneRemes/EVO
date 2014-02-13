#ifndef FILEREADER_H_
#define FILEREADER_H_

#include "Platform/Window.h"
#include <sstream>
#include <fstream>

class FileReader
{
public:
	FileReader();
	FileReader(const std::string filePath);
	~FileReader(void);

	void open(bool isBinary);
	void seek(int offset, int origin);
	void read(unsigned int count, char* buffer);
	unsigned int length();
	int tell();
	std::string loadFile(const std::string& fileName);

private:

	//FILE* file;
	std::ifstream stream;
	std::string filepath;
	

	unsigned int _length;
};

#endif