#pragma once
#include <string>
#include <glew.h>
#include <fstream>
#include "Texture.h"
#include <glm.hpp>
#include <gtc/matrix_transform.hpp>
#include <gtc/type_ptr.hpp>

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
	void SendMatrices(glm::mat4 model, glm::mat4 view, glm::mat4 projection);
private:
	GLuint shaders[2];
	GLuint prog;
	Texture texture;
};

