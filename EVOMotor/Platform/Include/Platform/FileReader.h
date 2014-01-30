#ifndef FILEREADER_H_
#define FILEREADER_H_

class FileReader
{
public:
	FileReader(const char* filePath);
	~FileReader(void);

	bool seek(int offset, int origin);
	bool read(unsigned int count, void* buffer);
};

#endif