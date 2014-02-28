#ifndef FILEREADER_H_
#define FILEREADER_H_

#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <Platform/OpenGL.hpp>
#include "Platform/debug.h"

#include <android/asset_manager.h>
#include <android/asset_manager_jni.h>

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
	FileReader(const char* path);
	~FileReader();

	static AAssetManager* manager;
	bool seek(int offset,int relation);
	bool read(unsigned int count, void*buffer);
	std::string loadFile(const std::string &fileName);
	static GLubyte* loadTGA(const std::string &fileName, tgaHeader &header);
	unsigned int length();
private:
	AAsset* asset;
	unsigned int _length;
};

#endif