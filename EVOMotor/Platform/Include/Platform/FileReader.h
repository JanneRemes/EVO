#ifndef FILEREADER_H_
#define FILEREADER_H_

#include "debug.h"

class FileReader
{
public:
	FileReader(const char* filePath);
	~FileReader(void);

	bool seek(int offset, int origin);
	bool read(unsigned int count, void* buffer);
	unsigned int length();

private:

	FILE* file;
	std::string filepath;

	unsigned int _length;
};

#endif