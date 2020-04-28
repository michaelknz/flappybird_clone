#pragma once
#include <string>
#include <glew.h>
#include <fstream>
#include "Texture.h"

class Shader
{
public:
	Shader();
	~Shader();
	void Init(const std::string& shader_name, const std::string& texture_file_name);
	void ShatUp();
	void bind();
	std::string Read_Shader(const std::string& shader_file);
	GLuint Create_Shader(const std::string& shader_text, GLuint type);
	void SendTextureUniform();
private:
	GLuint shaders[2];
	GLuint prog;
	Texture texture;
};

