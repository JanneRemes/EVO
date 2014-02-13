/**
 * @file graphics/TextureReader.h
 *
 * DevEngine - 3D Mobile Game Engine
 * Copyright 2013 Eetu 'Devenec' Oinasmaa
 */

#ifndef GRAPHICS_TEXTUREREADER_H
#define GRAPHICS_TEXTUREREADER_H

#include <Platform/png.h>

#include <Platform/Window.h>
#include <Platform/Texture.h>
#include "Platform/FileReader.h"

	class TextureReader
	{
	public:

		TextureReader();
		~TextureReader();

		Texture* read();

	private:

		png_struct* _png;
		png_info* _pngInfo;
		FileReader reader;

		GLubyte* _data;

		TextureReader(const TextureReader& textureReader);

		void initialisePNGReader(FileReader reader);
		unsigned char* readImageData();
		int textureFormat() const;

		static void verifySignature(FileReader reader);

		TextureReader& operator =(const TextureReader& textureReader);
	};

#endif