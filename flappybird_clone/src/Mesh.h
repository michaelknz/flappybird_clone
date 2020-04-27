#pragma once
#include <glew.h>
class Mesh
{
public:
	Mesh(float* VertexBuf, unsigned int size);
	~Mesh();
	void DrawMesh();
private:
	GLuint vao;
	GLuint vbo;
	unsigned int BufSize;
};

