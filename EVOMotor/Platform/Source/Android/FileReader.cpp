#include "Platform/Android/FileReader.h"

AAssetManager* FileReader::manager = 0;

FileReader::FileReader(const char* path)
{
	//asset = AAssetManager_open(FileReader::manager,path,2);
	//_length = AAsset_getLength(asset);
	//loadFile(path);
}

FileReader::~FileReader()
{
	AAsset_close(asset);
}

bool FileReader::seek(int offset, int relation)
{
	if(AAsset_seek(asset, offset, relation) != 1)
		return true;
	return false;
}

bool FileReader::read(unsigned int count, void*buffer)
{
	writeLog("%d %x", count, buffer);
	if(asset != NULL)
		if(AAsset_read(asset, buffer,count) >=0)
			return true;
	return false;
}

std::string FileReader::loadFile(const std::string &fileName)
{	
	//TODO: check for invalid filenames
	AAsset* asset = AAssetManager_open(FileReader::manager, fileName.c_str(), AASSET_MODE_UNKNOWN);
	writeLog("%s", fileName.c_str());
	if(asset == NULL)
	{
		writeLog("Asset = NULL");
	}
	_length = AAsset_getLength(asset);
	//off_t length = AAsset_getLength(asset);

	char* text = new char[_length+1];
	if(AAsset_read(asset, text, _length) < 1)
	{
		writeLog("File not loaded! Error! Error!");
	}

	text[_length] = 0;

	AAsset_close(asset);
	text[_length] = 0;
	std::string r(text);

	return r;
}

GLubyte* FileReader::loadTGA(const std::string &fileName, tgaHeader &header)
{
	AAsset* asset = AAssetManager_open(FileReader::manager, fileName.c_str(), AASSET_MODE_UNKNOWN);
	if(asset == NULL)
	{
		writeLog("Asset = NULL");
	}
    AAsset_read(asset, &header.idLength, 1);
    AAsset_read(asset, &header.colorMapType, 1);
    AAsset_read(asset, &header.type, 1);
    AAsset_seek(asset, 9, SEEK_CUR);
    AAsset_read(asset, &header.width, 2);
    AAsset_read(asset, &header.height, 2);
    AAsset_read(asset, &header.depth, 1);
    AAsset_read(asset, &header.descriptor, 1);
    AAsset_seek(asset, header.idLength, SEEK_CUR);
    
	//writeLog("spritewidth: %d, height: %d, depth: %d", header.width, header.height, header.depth);

    //24bit / 8 = 3 (RGB), 32bit / 8 = 4 (RGBA)
    int componentCount = header.depth/8;
    
    int size = componentCount * header.width * header.height;
    GLubyte* data = new GLubyte[size];
    
    AAsset_read(asset, data, size);
    
    //data is now BGRA so we format it to RGBA
    for(int i = 0; i < size; i += componentCount)
    {
        GLubyte temp = data[i];
        
        //Switch red and blue
        data[i] = data[i+2];
        data[i+2] = temp;
    }
    
    AAsset_close(asset);

	return data;

}


unsigned int FileReader::length()
{
	return _length;
}