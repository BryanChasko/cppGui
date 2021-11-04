#include "EBO.h"

/* Constructor that generates an Elements Buffer Object & links it to indices
An EBO is a buffer, just like a vertex buffer object, that stores indices that 
OpenGL uses to decide what vertices to draw. This so called indexed drawing, 
that allows us to make more complex geometry out of triangles, which are the basis
for openGL. */

EBO::EBO(GLuint* indices, GLsizeiptr size)
{
	glGenBuffers(1, &ID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, size, indices, GL_STATIC_DRAW);
}

// Bind our EBO indices in the buffer
void EBO::Bind()
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ID);
}

// Unbind our EBO from the buffer
void EBO::Unbind()
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

//Delete our EBO so it stops running
void EBO::Delete()
{
	glDeleteBuffers(1, &ID);
}