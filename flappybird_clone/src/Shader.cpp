#include "Shader.h"

Shader::Shader() {
	
}

Shader::~Shader() {
	
}

std::string Shader::Read_Shader(const std::string& shader_file) {
	std::ifstream file;
	file.open(shader_file.c_str());
	std::string line;
	std::string output;
	while (file.good()) {
		getline(file, line);
		output.append(line + "\n");
	}
	return output;
}

GLuint Shader::Create_Shader(const std::string& shader_text, GLuint type) {
	GLuint Shader = glCreateShader(type);
	const GLchar* p[1];
	p[0] = shader_text.c_str();
	GLint l[1];
	l[0] = shader_text.length();
	glShaderSource(Shader, 1, p, l);
	glCompileShader(Shader);
	return Shader;
}

void Shader::bind() {
	glUseProgram(prog);
	texture.bind();
	SendTextureUniform();
}

void Shader::Init(const std::string& shader_name, const std::string& texture_file_name) {
	prog = glCreateProgram();
	shaders[0] = Create_Shader(Read_Shader("shaders/" + shader_name + ".vs"), GL_VERTEX_SHADER);
	shaders[1] = Create_Shader(Read_Shader("shaders/" + shader_name + ".fs"), GL_FRAGMENT_SHADER);

	for (int i = 0; i < 2; ++i) {
		glAttachShader(prog, shaders[i]);
	}
	glLinkProgram(prog);
	GLint loglen;
	glGetProgramiv(prog, GL_INFO_LOG_LENGTH, &loglen);
	if (loglen > 0) {
		char* log = new char[loglen];
		GLsizei writen;
		glGetProgramInfoLog(prog, loglen, &writen, log);
		printf("%s\n", log);
		delete log;
	}
	texture.Init(texture_file_name);
}

void Shader::ShatUp() {
	for (int i = 0; i < 2; ++i) {
		glDetachShader(prog, shaders[i]);
	}

	glDeleteProgram(prog);
}

void Shader::SendTextureUniform() {
	glUniform1i(glGetUniformLocation(prog, "Texture"), 0);
}