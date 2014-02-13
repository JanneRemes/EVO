/**
 * @file graphics/TextureReader.h
 *
 * DevEngine - 3D Mobile Game Engine
 * Copyright 2013 Eetu 'Devenec' Oinasmaa
 */

#include <algorithm>
#include "Platform/TextureReader.h"
#include "Platform/debug.h"
#include <cstdint>

// External

static void* allocatePNGMemory(png_struct* png, const unsigned int size);
static void deallocatePNGMemory(png_struct* png, void* object);
static void handlePNGError(png_struct* png, const char* message);
static void handlePNGWarning(png_struct* png, const char* message);
static void readPNGData(png_struct* png, unsigned char* buffer, const unsigned int size);


// Public

TextureReader::TextureReader()
	: _png(NULL),
	  _pngInfo(NULL) { }

TextureReader::~TextureReader() { }

Texture* TextureReader::read()
{
	verifySignature(reader);
	initialisePNGReader(reader);

	const unsigned char* data = readImageData();
	const unsigned int width = png_get_image_width(_png, _pngInfo);
	const unsigned int height = png_get_image_height(_png, _pngInfo);
	
	_data = (GLubyte*)data;
	Texture* texture = new Texture(_data, width, height, 0);
	texture->setData(data);
	delete[] data;
	png_destroy_read_struct(&_png, &_pngInfo, NULL);

	return texture;
}


// Private

void TextureReader::initialisePNGReader(FileReader reader)
{
	_png = png_create_read_struct_2(PNG_LIBPNG_VER_STRING, NULL, handlePNGError, handlePNGWarning, NULL,
		allocatePNGMemory, deallocatePNGMemory);

	//CHECK_ERROR(_png == NULL, "Graphics::TextureReader", "Failed to initialise the PNG reader");
	png_set_read_fn(_png, &reader, readPNGData);
	png_set_sig_bytes(_png, 8);
	_pngInfo = png_create_info_struct(_png);
	//CHECK_ERROR(_pngInfo == NULL, "Graphics::TextureReader", "Failed to initialise the PNG reader info");
}

int TextureReader::textureFormat() const
{
	const unsigned int colorType = png_get_color_type(_png, _pngInfo);

	switch(colorType)
	{
		case PNG_COLOR_TYPE_RGB:
			return GL_RGB;

		case PNG_COLOR_TYPE_RGBA:
			return GL_RGBA;

		default:
			writeLog("Graphics::TextureReader", "The color type of the PNG file is not supported");
			return 0;
	}
}

unsigned char* TextureReader::readImageData()
{
	const int transforms = PNG_TRANSFORM_PACKING | PNG_TRANSFORM_STRIP_16;
	png_read_png(_png, _pngInfo, transforms, NULL);

	const unsigned int height = png_get_image_height(_png, _pngInfo);
	const unsigned int rowSize = png_get_rowbytes(_png, _pngInfo);
	unsigned char* data = new unsigned char[height * rowSize];
	unsigned char* row = data;
	unsigned char** rows = png_get_rows(_png, _pngInfo);

	for(unsigned int i = height - 1u; i != UINT32_MAX; --i)
	{
		std::copy(rows[i], rows[i] + rowSize, row);
		row += rowSize;
	}

	return data;
}

// Static

void TextureReader::verifySignature(FileReader reader)
{
	unsigned char signature[8u];
	reader.read(signature, 8u);
	const unsigned int result = png_sig_cmp(signature, 0u, 8u);
	//CHECK_ERROR(result != 0u, "Graphics::TextureReader", "The PNG file signature is invalid");
}


// External

namespace Content
{
	template<>
	ContentTypeReader<Texture>* ContentTypeReader<Texture>::reader()
	{
		return new TextureReader();
	}
}

static void* allocatePNGMemory(png_struct* png, const unsigned int size)
{
	return ::operator new(size);
}

static void deallocatePNGMemory(png_struct* png, void* object)
{
	return ::operator delete(object);
}

static void handlePNGError(png_struct* png, const char* message)
{
	//TRIGGER_ERROR("Graphics::TextureReader", "%s", message); // TODO: fix for Char16
}

static void handlePNGWarning(png_struct* png, const char* message)
{
	//TRIGGER_WARNING("Graphics::TextureReader", "%s", message); // TODO: fix for Char16
}

static void readPNGData(png_struct* png, unsigned char* buffer, const unsigned int size)
{
	FileReader* reader = static_cast<FileReader*>(png_get_io_ptr(png));

	if(reader->size() < reader->position() + size)
		png_error(png, "Reached end of file");

	reader->read(buffer, size);
}