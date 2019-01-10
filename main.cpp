
#include"shaderlib.h"
#include"RenderingContext.h"
#include "camera.h"
#include"CVoxBuffer.h"
#include "controller.h"
class AppPipline : public Pipline {
public:
	void Draw() override;
	VoxBuffer buffer = VoxBuffer(new CVoxBuffer);
	FpsCamera camera = camera::CreateFpsCamera();
	std::shared_ptr<FrameEventHandler> camera_controller=nullptr;
	AppPipline();
};


int main() {
	RenderingContextFactory rcFactory;
	auto rc = rcFactory.CreateGLFWContext();
	shaderlib::loadshaders();
	auto pipline = new AppPipline;
	pipline->buffer->vertex_array.push_back({ 0,0,0,1,0,0 });
	pipline->camera->position = glm::vec3(2, 3, 4);
	pipline->camera->yall = 29.6;
	pipline->camera->pitch = -32.6;
	rc->pipline = pipline;
	rc->Run();
}

void AppPipline::Draw()
{
	auto MV = camera->GetModelView();
	auto MVP = camera->GetMVP();
	shaderlib::vox_shader->MV.Set(MV);
	shaderlib::vox_shader->MVP.Set(MVP);
	shaderlib::vox_shader->UseProgram();
	this->camera_controller->FrameUpdate();
	buffer->Draw();



}

AppPipline::AppPipline()
{
	camera_controller = camera->CreateController();
}
