
#include"shaderlib.h"
#include"RenderingContext.h"
#include "camera.h"
#include"CVoxBuffer.h"
#include "controller.h"
#include "rendertarget.h"
#include<chrono>
#include<iostream>
using namespace std;


#define MOVEDIR_X_DEC 1
#define MOVEDIR_X_INC 2
#define MOVEDIR_Y_DEC 4
#define MOVEDIR_Y_INC 8
#define MOVEDIR_Z_DEC 16
#define MOVEDIR_Z_INC 32

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

class CursorGraphics : public Renderable {
	// 通过 Renderable 继承
public:
	union {
		int pos[3];
		struct {
			int x;
			int y;
			int z;
		};
	};
private:
	virtual void * GetVertexBufferPointer() override
	{
		return pos;
	}
	virtual int GetPrimitiveCount() override
	{
		return 1;
	}
	virtual GLenum GetPrimitiveType() override
	{
		return GL_POINTS();
	}
	virtual GLenum GetPrimitiveSize() override
	{
		return sizeof(int) * 3;
	}
	virtual void SetAttributes(std::vector<VERTEX_ATTRIBUTE>& attributes) override
	{
		attributes.push_back({ 0, 3, GL_FLOAT, GL_FALSE, 0, 0 });
	}
};

#define DefineRenderableObject(type, identifer) shared_ptr<type> identifer = CreateRenderable<type>()

class Quad : public Renderable {
	float vertices[16]{
		-1,  1, 0, 1,
		-1, -1, 0, 0,
		 1,  1, 1, 1,
		 1, -1, 1, 0
	};
	// 通过 Renderable 继承
	virtual void * GetVertexBufferPointer() override { return vertices; }
	virtual int GetPrimitiveCount() override { return 4; }
	virtual GLenum GetPrimitiveType() override { return GL_TRIANGLE_STRIP; }
	virtual GLenum GetPrimitiveSize() override { return sizeof(float) * 4; }
	virtual void SetAttributes(std::vector<VERTEX_ATTRIBUTE>& attributes) override
	{
		attributes.push_back({ 0,2,GL_FLOAT, GL_FALSE, sizeof(float) * 4,0 });
		attributes.push_back({ 1,2,GL_FLOAT, GL_FALSE, sizeof(float) * 4,sizeof(float) * 2 });
	}

};

class EditorPipline : public Pipline {
public:
	RenderTarget geometry;
	RenderTarget screen = CRenderTarget::Screen();
	void Draw() override;
	//VoxBuffer buffer = VoxBuffer(new CVoxBuffer);
	//VoxBuffer buffer = CreateRenderable<CVoxBuffer>();
	VoxBuffer buffer = nullptr;
	DefineRenderableObject(EditorAxisLines, axis);
	DefineRenderableObject(EditorSkybox, skybox);
	DefineRenderableObject(CursorGraphics, cursor);
	DefineRenderableObject(Quad, quad);
	//shared_ptr<EditorAxisLines> axis = CreateRenderable<EditorAxisLines>();
	//shared_ptr<EditorSkybox> skybox = CreateRenderable<EditorSkybox>();

	//FpsCamera camera = camera::CreateFpsCamera();
	OrbitCamera camera = camera::CreateOrbitCamera();
	std::shared_ptr<FrameEventHandler> camera_controller = nullptr;
	/*glm::vec2 pick;
	int pick_vox_id;
	int pick_vox_face;*/
	EditorPipline();
};


class EditorCamera : public CCamera {
	glm::vec3 focusPos;
	float yall;
	float pitch;
};

class CursorController;

class EditorCursor {
	glm::ivec3 selection_begin_pos;
	glm::ivec3 range = glm::ivec3(32, 32, 32);
	bool selectingState = false;
	CursorController* controller = NULL;

public:
	int step = 1;
	glm::ivec3 pos;
	shared_ptr<CursorGraphics>graphics = nullptr;
	void Move(int direction);
	void SetPos(int x, int y, int z);
	void BeginSelect();
	void EndSelect();
	void GetSelection(glm::ivec3 & min, glm::ivec3 & max);

	void AttachController(CursorController* controller);
	void DetachController();

};

class CursorController : public KeyEventHandler {
public:
	EditorCamera* camera = NULL;
	EditorCursor* cursor = NULL;

	// 通过 KeyEventHandler 继承
	virtual void OnKeyEvent(int key, int scancode, int action, int mods) override
	{
		//cout << key << "  " << action << endl;
		if (cursor == NULL) {
			return;
		}

		if (key == GLFW_KEY_LEFT_SHIFT) {
			if (action) {
				cursor->step = 4;
			}
			else {
				cursor->step = 1;
			}
		}

		if (action) {

			switch (key)
			{
			case GLFW_KEY_W:
				cursor->Move(MOVEDIR_Z_DEC);
				break;
			case GLFW_KEY_S:
				cursor->Move(MOVEDIR_Z_INC);
				break;
			case GLFW_KEY_A:
				cursor->Move(MOVEDIR_X_DEC);
				break;
			case GLFW_KEY_D:
				cursor->Move(MOVEDIR_X_INC);
				break;
			case GLFW_KEY_Q:
				cursor->Move(MOVEDIR_Y_DEC);
				break;
			case GLFW_KEY_E:
				cursor->Move(MOVEDIR_Y_INC);
				break;

			default:
				break;
			}
		}
		//cout << cursor->pos.x << cursor->pos.y << cursor->pos.z << endl;
	}
};

class Editor :public KeyEventHandler, public MousePositionEventHandler {
public:
	VoxBuffer buffer = CreateRenderable<CVoxBuffer>();
	EditorCursor cursor;
	EditorPipline* pipline;
	void FillSelection();
	void EraseSelection();
	void Undo();
	void Redo();
	Editor();

	// 通过 KeyEventHandler 继承
	virtual void OnKeyEvent(int key, int scancode, int action, int mods) override
	{
		if (action) {
			if (key == GLFW_KEY_ENTER) {
				FillSelection();
			}
			if (key == GLFW_KEY_DELETE) {
				EraseSelection();
			}
			if (key == GLFW_KEY_V) {
				cursor.BeginSelect();
			}
			if (key == GLFW_KEY_ESCAPE) {
				cursor.EndSelect();
			}
		}
		if (key == GLFW_KEY_TAB) {
			if (action) {
				shaderlib::quad_shader->option.Set(1);
			}
			else {
				shaderlib::quad_shader->option.Set(0);
			}
		}
	}

	// 通过 MousePositionEventHandler 继承
	virtual void OnMousePosition(double x, double y) override
	{
		//cout << x << "," << y << "  ->  ";
		/*pipline->pick.x = x;
		pipline->pick.y = y;*/

		glm::vec4 pixel;
		pipline->geometry->ReadPixel(3, x, 600 - y, pixel);
		//cout << pixel.x << "  " << pixel.y << endl;
		int vox_id = pixel.x - 100000;
		int vox_face = pixel.y;
		if (vox_id > 0) {
			/*pick_vox_id = vox_id;
			pick_vox_face = vox_face;*/
			cursor.SetPos(vox_id % 32, (vox_id / 32) % 32, (vox_id / 1024) % 32);
		}
		else {
			/*pick_vox_id = -1;
			pick_vox_face = -1;*/
		}

		
	}
};


void Editor::FillSelection()
{
	glm::ivec3 min;
	glm::ivec3 max;
	cursor.GetSelection(min, max);
	const int sizeX = 32;
	const int sizeY = 32;
	for (int x = min.x; x < max.x; x++) {
		for (int y = min.y; y < max.y; y++) {
			for (int z = min.z; z < max.z; z++) {
				buffer->vertex_array[z*sizeY*sizeX + y * sizeX + x].size = 1;
				buffer->vertex_array[z*sizeY*sizeX + y * sizeX + x].palette_index = 1;
				//cout << "FILL " << x << " " << y << " " << z << endl;
			}
		}
	}

}

void Editor::EraseSelection()
{
	glm::ivec3 min;
	glm::ivec3 max;
	cursor.GetSelection(min, max);
	const int sizeX = 32;
	const int sizeY = 32;
	for (int x = min.x; x < max.x; x++) {
		for (int y = min.y; y < max.y; y++) {
			for (int z = min.z; z < max.z; z++) {
				buffer->vertex_array[z*sizeY*sizeX + y * sizeX + x].size = 0;
			}
		}
	}
}

Editor::Editor() {
	buffer->vertex_array.resize(32768, { 0,0,0,0,-1,0 });
	int i = 0;
	for (int z = 0; z < 32; z++) {
		for (int y = 0; y < 32; y++) {
			for (int x = 0; x < 32; x++) {
				buffer->vertex_array[i].x = x;
				buffer->vertex_array[i].y = y;
				buffer->vertex_array[i].z = z;
				i++;
			}
		}
	}
	pipline = new EditorPipline;
	pipline->buffer = this->buffer;
	cursor.graphics = pipline->cursor;
	cursor.SetPos(0, 0, 0);
}


int main() {
	RenderingContextFactory rcFactory;
	auto rc = rcFactory.CreateGLFWContext();
	shaderlib::loadshaders();
	auto editor = new Editor;
	editor->cursor.AttachController(new CursorController);
	auto pipline = editor->pipline;
	//auto pipline = new EditorPipline;
	//pipline->buffer->vertex_array.push_back({ 0,0,0,1,0,0 });
	pipline->camera->center = glm::vec3(16, 0, 16);
	pipline->camera->yall = -135;
	pipline->camera->pitch = 30;
	rc->pipline = pipline;
	rc->Run();
}

void EditorPipline::Draw()
{
	this->camera_controller->FrameUpdate();

	auto MV = camera->GetModelView();
	auto MVP = camera->GetMVP();
	auto V = camera->GetView();
	auto P = camera->GetProjection();
	auto VP = P * V;
	auto VP_inv = glm::inverse(VP);

	geometry->Pass([&] {

		shaderlib::skybox_shader->VP_inv.Set(VP_inv);
		shaderlib::skybox_shader->UseProgram();
		skybox->Draw();
		glClear(GL_DEPTH_BUFFER_BIT);

		shaderlib::vox_shader->MV.Set(MV);
		shaderlib::vox_shader->MVP.Set(MVP);
		auto hightlight = glm::vec3(1, 0, 0);
		shaderlib::vox_shader->highlight_color.Set(hightlight);
		auto now = std::chrono::system_clock::now();
		auto milliseconds = std::chrono::duration_cast<chrono::milliseconds>(now.time_since_epoch()).count();
		auto time = milliseconds % 10000000 / 100.0;
		shaderlib::vox_shader->time.Set(time);
		shaderlib::vox_shader->selection_id.Set(cursor->z * 1024 + cursor->y * 32 + cursor->x + 1);
		shaderlib::vox_shader->UseProgram();
		buffer->Draw();

		shaderlib::axis_shader->MVP.Set(MVP);
		shaderlib::axis_shader->UseProgram();
		axis->Draw();

		shaderlib::cursor_shader->MVP.Set(MVP);
		shaderlib::cursor_shader->UseProgram();
		cursor->Draw();
	});


	screen->Pass([&] {
		shaderlib::quad_shader->color_texture.Set(geometry->color_buffers[0]);
		shaderlib::quad_shader->index_texture.Set(geometry->color_buffers[3]);
		shaderlib::quad_shader->UseProgram();
		quad->Draw();
	});
	//cout << glGetError() << endl;
	//glm::vec4 pixel;
	//geometry->ReadPixel(3, pick.x, 600 - pick.y, pixel);
	////cout << pixel.x << "  " << pixel.y << endl;
	//int vox_id = pixel.x - 100000;
	//int vox_face = pixel.y;
	//if (vox_id > 0) {
	//	pick_vox_id = vox_id;
	//	pick_vox_face = vox_face;
	//}
	//else {
	//	pick_vox_id = -1;
	//	pick_vox_face = -1;
	//}
}

EditorPipline::EditorPipline()
{
	camera_controller = camera->CreateController();
	geometry = CRenderTarget::Create();
	geometry->CreateColorBuffers(800, 600, 4);
	geometry->CreateDepthBuffer(800, 600);
}


void EditorCursor::Move(int direction)
{
	if (direction & MOVEDIR_X_DEC) { SetPos(pos.x - step, pos.y, pos.z); }
	if (direction & MOVEDIR_X_INC) { SetPos(pos.x + step, pos.y, pos.z); }
	if (direction & MOVEDIR_Y_DEC) { SetPos(pos.x, pos.y - step, pos.z); }
	if (direction & MOVEDIR_Y_INC) { SetPos(pos.x, pos.y + step, pos.z); }
	if (direction & MOVEDIR_Z_DEC) { SetPos(pos.x, pos.y, pos.z - step); }
	if (direction & MOVEDIR_Z_INC) { SetPos(pos.x, pos.y, pos.z + step); }
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
	graphics->x = x;
	graphics->y = y;
	graphics->z = z;
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

void EditorCursor::AttachController(CursorController * controller)
{
	this->controller = controller;
	controller->cursor = this;
}

void EditorCursor::DetachController()
{
	if (controller) {
		controller->cursor = NULL;
		controller = NULL;
	}
}
