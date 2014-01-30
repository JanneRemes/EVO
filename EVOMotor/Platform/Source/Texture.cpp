#include "Platform/Texture.h"


Texture::Texture(const char * imagepath)
{

}


Texture::~Texture(void)
{

}

GLubyte* Texture::loadTGA(const std::string& fileName, tgaHeader &header)
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