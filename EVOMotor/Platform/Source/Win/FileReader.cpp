#include "Platform/FileReader.h"
#include <cassert>

//
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

FileReader::FileReader(const std::string& path)
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

GLubyte* FileReader::loadTGA(const std::string& fileName, tgaHeader &header)
{
	std::ifstream file;
	file.open(fileName, std::ios::binary);

	file.read((char*)&header.idLength,1);
	file.read((char*)&header.colorMapType,1);
	file.read((char*)&header.type,1);
	file.seekg(9,std::ios_base::cur);
	file.read((char*)&header.width,2);
	file.read((char*)&header.height,2);
	file.read((char*)&header.depth,1);
	file.read((char*)&header.descriptor,1);
	file.seekg(header.idLength,std::ios_base::cur);

	//24bit / 8 = 3 (RGB), 32bit / 8 = 4 (RGBA)
	int componentCount = header.depth/8;

	int size = componentCount * header.width * header.height;
	GLubyte* data = new GLubyte[size];

	file.read((char*)data,size);

	//data is now BGRA for some reason so we format it to RGBA
	for(int i = 0;i < size; i+= componentCount)
	{
		GLubyte temp = data[i];

		//Switch red and blue
		data[i] = data[i+2];
		data[i+2] = temp;
	}

	file.close();

	return data;
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