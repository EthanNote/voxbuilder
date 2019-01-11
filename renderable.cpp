#include "renderable.h"

void Renderable::SetAttributes(std::vector<VERTEX_ATTRIBUTE>& attributes)
{
}

void * Renderable::GetVertexBufferPointer()
{
	return nullptr;
}


int Renderable::GetPrimitiveCount()
{
	return 0;
}

//
//Renderable::Renderable()
//{
//	this->SetAttributes(this->attributes);
//}

void Renderable::SetAttributes()
{
	SetAttributes(attributes);
}

void Renderable::Draw()
{
	int primitiveCount = GetPrimitiveCount();
	auto primitiveType = GetPrimitiveType();
	auto primitiveSize = GetPrimitiveSize();
	if (primitiveCount <= 0 || primitiveSize <= 0) {
		return;
	}
	void* vptr = GetVertexBufferPointer();
	glBindVertexArray(VAO);
	if (VAO <= 0) {
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		EnableAttributes();
		bool isPointerSet = false;
		if (VBO <= 0) {
			if (vptr) {
				for (auto i = attributes.begin(); i != attributes.end(); i++) {
					isPointerSet = true;
					glVertexAttribPointer(i->index, i->size, i->type, i->normalized, i->stride, (GLbyte*)vptr + i->buffer_byte_offset);
				}
			}
		}
		else {
			for (auto i = attributes.begin(); i != attributes.end(); i++) {
				isPointerSet = true;
				glVertexAttribPointer(i->index, i->size, i->type, i->normalized, i->stride, (void*)i->buffer_byte_offset);
			}
		}
		if (isPointerSet) {
			glDrawArrays(primitiveType, 0, primitiveCount);

		}
		DisableAttributes();
	}
	else {
		glDrawArrays(primitiveType, 0, primitiveCount);
	}
}



void Renderable::EnableAttributes()
{
	for (auto i = attributes.begin(); i != attributes.end(); i++) {
		glEnableVertexAttribArray(i->index);
	}
}

void Renderable::DisableAttributes()
{
	for (auto i = attributes.begin(); i != attributes.end(); i++) {
		glDisableVertexAttribArray(i->index);
	}
}

