#include "Platform/FileReader.h"


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

FileReader::FileReader(const char* path)
{
	filepath = path;
	file = fopen(filepath.c_str(),"rb");

	//Check if file is found
	if(!file)
	{
		writeLog("\n-----------------\nFile opening failed! File not found?\n-----------------\n");
		return;
	}

	fseek(file, 0, SEEK_END);
	_length = ftell(file);
	fseek(file, 0, SEEK_SET);
}


FileReader::~FileReader(void)
{
	//Close file
	fclose(file);
}

bool FileReader::seek(int offset, int relation)
{
	//Seek file
	if(fseek(file, offset, relation) != 1)
		return true;
	return false;
}

bool FileReader::read(unsigned int count, void*buffer)
{
	//If found file, read it
	if(file != NULL)
		if(fread(buffer, 1, count, file)==count)
			return true;
	return false;
}

unsigned int FileReader::length()
{
	return _length;
}
