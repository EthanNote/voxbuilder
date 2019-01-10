#pragma once
#include <GL\glew.h>
#include <vector>
#include "camera.h"

struct VERTEX_ATTRIBUTE {
	GLuint index;
	GLint size;
	GLenum type;
	GLboolean normalized;
	GLsizei stride;
	unsigned int buffer_byte_offset;
};

//namespace vertex_attribute {
//	VERTEX_ATTRIBUTE end();
//}
class Renderable
{
protected:
	std::vector<VERTEX_ATTRIBUTE> attributes;
	GLuint VAO=0;
	GLuint VBO=0;
	GLenum PrimitiveType = GL_POINTS;
	GLuint PrimitiveSize = 0;
	virtual void* GetVertexBufferPointer();
	virtual int GetPrimitiveCount();
public:
	void Draw();
	void EnableAttributes();
	void DisableAttributes();
};

