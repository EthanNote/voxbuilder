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
	GLuint VAO = 0;
	GLuint VBO = 0;
	std::vector<VERTEX_ATTRIBUTE> attributes;
protected:
	virtual void* GetVertexBufferPointer() = 0;
	virtual int GetPrimitiveCount() = 0;
	virtual GLenum GetPrimitiveType() = 0;
	virtual GLenum GetPrimitiveSize() = 0;
	virtual void SetAttributes(std::vector<VERTEX_ATTRIBUTE>& attributes) = 0;
public:
	void SetAttributes();
	void Draw();
	void EnableAttributes();
	void DisableAttributes();
};

template<class T>
inline std::shared_ptr<T> CreateRenderable()
{
	auto ptr = new T;
	((Renderable*)ptr)->SetAttributes();
	return std::shared_ptr<T>(ptr);
}
