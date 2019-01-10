#pragma once
#include<memory>
#include<vector>
using namespace std;

#include "CRenderableVertex.h"
#include "renderable.h"
class CVoxBuffer :public Renderable
{
	void* GetVertexBufferPointer() override;
	int GetPrimitiveCount();
public:

	vector<RenderableVertex> vertex_array;
	void write(string fname);

	void read(string fname);

	CVoxBuffer();
	~CVoxBuffer();
};

typedef shared_ptr<CVoxBuffer> VoxBuffer;
