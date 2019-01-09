#include "CVoxBuffer.h"
#include<string>
#include<iostream>
#include<fstream>

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
}


CVoxBuffer::~CVoxBuffer()
{
}
