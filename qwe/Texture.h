#pragma once

#include <string>
#include <GL/glew.h>
#include "Debug.h"
class Texture
{
public:
	Texture(const std::string& fileName);
	~Texture();

	void Bind(unsigned int unit);

private:
	GLuint _texture;

};

