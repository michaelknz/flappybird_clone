#include "Mesh.h"

Mesh::Mesh() {

}

Mesh::~Mesh() {
	
}

void Mesh::DrawMesh() {
	glBindVertexArray(vao);
	glDrawArrays(GL_TRIANGLES, 0, BufSize);
	glBindVertexArray(0);
}

void Mesh::Init(float* VertexBuf, unsigned int size, unsigned int line_size) {
	BufSize = size;

	glGenVertexArrays(1, &vao);
	glGenBuffers(1, &vbo);

	glBindVertexArray(vao);

	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, size * sizeof(float), VertexBuf, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, line_size * sizeof(float), 0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, line_size * sizeof(float), (GLvoid*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	glBindVertexArray(0);
}

void Mesh::ShatUp() {
	glDeleteBuffers(1, &vbo);
	glDeleteVertexArrays(1, &vao);
}