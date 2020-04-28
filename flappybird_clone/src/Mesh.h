#pragma once
#include <glew.h>
class Mesh
{
public:
	Mesh();
	~Mesh();
	void Init(float* VertexBuf, unsigned int size, unsigned int line_size);
	void ShatUp();
	void DrawMesh();
private:
	GLuint vao;
	GLuint vbo;
	unsigned int BufSize;
};

