#ifndef TEXT_H_
#define TEXT_H_

#include <iostream>
#include <vector>
#include <fstream>
#include <Platform/OpenGL.hpp>
#include <incl/glm/glm.hpp>

#include <incl/freetype-gl/freetype-gl.h>
#include <incl/freetype-gl/vertex-buffer.h>
#include "Platform/Shader.h"
#include "Platform/Viewport.h"
#include "Platform/Camera.h"

typedef struct {
    float x, y, z;    // position
    float s, t;       // texture
    float r, g, b, a; // color
} vertex_t;

class Text : public Object
{
public:
	Text(const std::string& fontPath, const float fontSize, Viewport* viewport);
	~Text();
	void addText(wchar_t* text, const glm::vec4& color = glm::vec4(1,1,1,1));
	virtual void draw(glm::mat4 &projectionMatrix);
	virtual void update(float dt);
private:
	texture_font_t* font;
	const float m_fontSize;

	vertex_buffer_t *buffer;

	std::string fontPath;
	std::string m_path;

	texture_atlas_t* m_atlas;
	glm::vec2 m_lastPos;

	GLuint shader; 
	Viewport* _viewport;

};

#endif