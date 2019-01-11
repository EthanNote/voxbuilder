#pragma once
#include<memory>
#include<vector>
using namespace std;

#include "CRenderableVertex.h"
#include "renderable.h"
class CVoxBuffer :public Renderable
{
	void SetAttributes(std::vector<VERTEX_ATTRIBUTE>& attributes) override;
	void* GetVertexBufferPointer() override;
	int GetPrimitiveCount() override;
	GLenum GetPrimitiveType() override;
	GLenum GetPrimitiveSize() override;
public:

	vector<RenderableVertex> vertex_array;
	void write(string fname);

	void read(string fname);

	//CVoxBuffer();
	//~CVoxBuffer();
};

typedef shared_ptr<CVoxBuffer> VoxBuffer;
