#pragma once
#include <SOIL.h>
#include <glew.h>
#include <string>

class Texture
{
public:
	Texture();
	~Texture();
	void Init(const std::string& image_name);
	void bind();
private:
	GLuint texture;
};

