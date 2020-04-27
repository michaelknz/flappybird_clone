#pragma once
#include <string>
#include <glew.h>
#include <fstream>

class Shader
{
public:
	Shader(const std::string& shader_name);
	~Shader();
	void bind();
	std::string Read_Shader(const std::string& shader_file);
	GLuint Create_Shader(const std::string& shader_text, GLuint type);
private:
	GLuint shaders[2];
	GLuint prog;
};

