#include "Platform/FileReader.h"
#include <cassert>

std::string FileReader::loadFile(const std::string& fileName)
{
	std::stringstream stream;
	std::ifstream file;
	file.open(fileName, std::ios::in);

	if(file.is_open())
	{
		stream << file.rdbuf();
		file.close();
		return stream.str();
	}
	else
	{
		std::cout << "File not found" << std::endl;
	}
	return "";
}

FileReader::FileReader(const std::string path)
	: filepath(path)
{
}

void FileReader::open(bool isBinary)
{
	std::ios_base::openmode mode = std::ios::in;
	if(isBinary)
	{
		mode |= std::ios::binary;
	}
	stream.open(filepath,mode);

	assert(stream.is_open());

	seek(std::ios::end,0);
	//stream.seekg(std::ios::end);
	_length = stream.tellg();
	//stream.seekg(std::ios::beg);
	seek(std::ios::beg,0);
	
}

FileReader::~FileReader(void)
{
}

int FileReader::tell()
{
	return stream.tellg();
}
void FileReader::seek(int offset, int relation)
{
	//Seek file
	stream.seekg(offset,relation);
	assert(stream.good());
}

void FileReader::read(unsigned int count, char* buffer)
{
	//If found file, read it
	stream.read(buffer,count);
	assert(stream.good());
}

unsigned int FileReader::length()
{
	return _length;
}