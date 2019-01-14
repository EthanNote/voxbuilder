
#include"shaderlib.h"
#include"RenderingContext.h"
#include "camera.h"
#include"CVoxBuffer.h"
#include "controller.h"
#include<iostream>
using namespace std;


struct LINE {
	float x;
	float y;
	float z;
	float r;
	float g;
	float b;
};

class EditorAxisLines : public Renderable {
public:
	float vertices[36]{
		0,0,0,1,0,0,  100,0,0,1,0,0,
		0,0,0,0,1,0,  0,100,0,0,1,0,
		0,0,0,0,0,1,  0,0,100,0,0,1
	};

	vector<LINE> lines;

	// 通过 Renderable 继承
	virtual void * GetVertexBufferPointer() override { return &lines[0]; }
	virtual int GetPrimitiveCount() override { return lines.size(); }
	virtual GLenum GetPrimitiveType() override { return GL_LINES; }
	virtual GLenum GetPrimitiveSize() override { return sizeof(float) * 12; }
	virtual void SetAttributes(std::vector<VERTEX_ATTRIBUTE>& attributes) override
	{
		attributes.push_back({ 0,3, GL_FLOAT, GL_FALSE, sizeof(float) * 6, 0 });
		attributes.push_back({ 1,3, GL_FLOAT, GL_FALSE, sizeof(float) * 6, sizeof(float) * 3 });
	}
	EditorAxisLines() {
		float g = 0.5;
		lines.push_back({ 0, 0, 0, 1, 0, 0 });
		lines.push_back({ 32, 0, 0, 1, 0, 0 });
		lines.push_back({ 0, 0, 0, 0, 0, 1 });
		lines.push_back({ 0, 0, 32, 0, 0, 1 });
		for (int i = 1; i <= 32; i++) {
			if (i % 8 == 0) {
				g = 0.5;
			}
			else {
				g = 0.2;
			}
			lines.push_back({ (float)i, 0, 0, g, g, g });
			lines.push_back({ (float)i, 0, 32, g, g, g });
			lines.push_back({ 0, 0, (float)i, g, g, g });
			lines.push_back({ 32, 0, (float)i, g, g, g });
		}
	}
};

class EditorSkybox : public Renderable {
	// 通过 Renderable 继承
	float vertex[8]{
		-1,1,		-1,-1,		1,1,		1,-1,
	};
	virtual void * GetVertexBufferPointer() override
	{
		return vertex;
	}
	virtual int GetPrimitiveCount() override
	{
		return 4;
	}
	virtual GLenum GetPrimitiveType() override
	{
		return GL_TRIANGLE_STRIP;
	}
	virtual GLenum GetPrimitiveSize() override
	{
		return 1;
	}
	virtual void SetAttributes(std::vector<VERTEX_ATTRIBUTE>& attributes) override
	{
		attributes.push_back({ 0,2,GL_FLOAT, GL_FALSE, sizeof(float) * 2, 0 });
	}
};

#define DefineRenderableObject(type, identifer) shared_ptr<type> identifer = CreateRenderable<type>()

class AppPipline : public Pipline {
public:
	void Draw() override;
	//VoxBuffer buffer = VoxBuffer(new CVoxBuffer);
	VoxBuffer buffer = CreateRenderable<CVoxBuffer>();
	DefineRenderableObject(EditorAxisLines, axis);
	DefineRenderableObject(EditorSkybox, skybox);
	//shared_ptr<EditorAxisLines> axis = CreateRenderable<EditorAxisLines>();
	//shared_ptr<EditorSkybox> skybox = CreateRenderable<EditorSkybox>();

	FpsCamera camera = camera::CreateFpsCamera();
	std::shared_ptr<FrameEventHandler> camera_controller = nullptr;
	AppPipline();
};


class EditorCamera : public CCamera {
	glm::vec3 focusPos;
	float yall;
	float pitch;
};

class EditorCursor {
	glm::ivec3 selection_begin_pos;
	glm::ivec3 range = glm::ivec3(32, 32, 32);
	bool selectingState = false;
public:
	glm::ivec3 pos;
	void Move(int direction);
	void SetPos(int x, int y, int z);
	void BeginSelect();
	void EndSelect();
	void GetSelection(glm::ivec3 & min, glm::ivec3 & max);
};

class CursorController {
	EditorCamera* camera;
	EditorCursor* cursor;
};

class Editor {
public:
	VoxBuffer buffer = CreateRenderable<CVoxBuffer>();
	EditorCursor cursor;
	void FillSelection();
	void EraseSelection();
	void Undo();
	void Redo();
	Editor();
};


Editor::Editor() {
	buffer->vertex_array.resize(32768, { 0,0,0,-1,0,0 });
}


int main() {
	RenderingContextFactory rcFactory;
	auto rc = rcFactory.CreateGLFWContext();
	shaderlib::loadshaders();
	auto pipline = new AppPipline;
	pipline->buffer->vertex_array.push_back({ 0,0,0,1,0,0 });
	pipline->camera->position = glm::vec3(-16, 24, -16);
	pipline->camera->yall = -135;
	pipline->camera->pitch = -30;
	rc->pipline = pipline;
	rc->Run();
}

void AppPipline::Draw()
{
	this->camera_controller->FrameUpdate();

	auto MV = camera->GetModelView();
	auto MVP = camera->GetMVP();
	auto V = camera->GetView();
	auto P = camera->GetProjection();
	auto VP = P * V;
	auto VP_inv = glm::inverse(VP);
	shaderlib::skybox_shader->VP_inv.Set(VP_inv);
	shaderlib::skybox_shader->UseProgram();
	skybox->Draw();
	glClear(GL_DEPTH_BUFFER_BIT);

	shaderlib::vox_shader->MV.Set(MV);
	shaderlib::vox_shader->MVP.Set(MVP);
	shaderlib::vox_shader->UseProgram();
	buffer->Draw();

	shaderlib::axis_shader->MVP.Set(MVP);
	shaderlib::axis_shader->UseProgram();
	axis->Draw();

	//cout << glGetError() << endl;
}

AppPipline::AppPipline()
{
	camera_controller = camera->CreateController();
}

#define MOVEDIR_X_DEC 1
#define MOVEDIR_X_INC 2
#define MOVEDIR_Y_DEC 4
#define MOVEDIR_Y_INC 8
#define MOVEDIR_Z_DEC 16
#define MOVEDIR_Z_INC 32
void EditorCursor::Move(int direction)
{
	if (direction & MOVEDIR_X_DEC) { SetPos(pos.x - 1, pos.y, pos.z); }
	if (direction & MOVEDIR_X_INC) { SetPos(pos.x + 1, pos.y, pos.z); }
	if (direction & MOVEDIR_Y_DEC) { SetPos(pos.x, pos.y - 1, pos.z); }
	if (direction & MOVEDIR_Y_INC) { SetPos(pos.x, pos.y + 1, pos.z); }
	if (direction & MOVEDIR_Z_DEC) { SetPos(pos.x, pos.y, pos.z - 1); }
	if (direction & MOVEDIR_Z_INC) { SetPos(pos.x, pos.y, pos.z + 1); }
}

void EditorCursor::SetPos(int x, int y, int z)
{
	if (x < 0 || x >= range.x ||
		y < 0 || y >= range.x ||
		z < 0 || z >= range.x
		) {
		return;
	}
	pos = glm::ivec3(x, y, z);
}

void EditorCursor::BeginSelect()
{
	selection_begin_pos = pos;
	selectingState = true;
}

void EditorCursor::EndSelect()
{
	selectingState = false;
}

#define MIN(x, y) (x>y?y:x)
#define MAX(x, y) (x>y?x:y)

void EditorCursor::GetSelection(glm::ivec3 & min, glm::ivec3 & max)
{
	if (selectingState) {
		min = glm::ivec3(MIN(selection_begin_pos.x, pos.x), MIN(selection_begin_pos.y, pos.y), MIN(selection_begin_pos.z, pos.z));
		max = glm::ivec3(MAX(selection_begin_pos.x, pos.x) + 1, MAX(selection_begin_pos.y, pos.y) + 1, MAX(selection_begin_pos.z, pos.z) + 1);
	}
	else {
		min = pos;
		max = pos + glm::ivec3(1);
	}
}
