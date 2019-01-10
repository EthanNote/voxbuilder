#include "CVoxBuffer.h"
#include<string>
#include<iostream>
#include<fstream>

void * CVoxBuffer::GetVertexBufferPointer()
{
	if(vertex_array.size()<=0)
		return nullptr;
	return &vertex_array[0];
}

int CVoxBuffer::GetPrimitiveCount()
{
	return vertex_array.size();
}

void CVoxBuffer::write(string fname)
{
	ofstream output(fname.c_str(), ios::binary | ios::out);
	if (output.is_open()) {
		output.write((char*)&vertex_array[0], sizeof(RenderableVertex)*vertex_array.size());
	}

}

void CVoxBuffer::read(string fname)
{
	vertex_array.clear();
	ifstream input(fname.c_str(), ios::binary);
	if (input.is_open()) {
		while (!input.eof())
		{
			RenderableVertex v;
			input.read((char*)&v, sizeof(RenderableVertex));
			vertex_array.push_back(v);
		}
	}
}

CVoxBuffer::CVoxBuffer()
{
	this->attributes.push_back({ 0, 4, GL_FLOAT, GL_FALSE, sizeof(RenderableVertex), 0 });
	this->attributes.push_back({ 1, 2, GL_FLOAT, GL_FALSE, sizeof(RenderableVertex), 4*sizeof(float) });
	this->PrimitiveSize = sizeof(RenderableVertex);
	this->PrimitiveType = GL_POINTS;
}


CVoxBuffer::~CVoxBuffer()
{
}
