#include "CViewer.h"
#include"shaderlib.h"


void CViewer::Draw()
{
	auto MV = this->camera->GetModelView();
	auto MVP = this->camera->GetMVP();
	shaderlib::vox_shader->MVP.Set(MVP);
	shaderlib::vox_shader->MV.Set(MV);

	this->buffer->Draw();
	
}

CViewer::CViewer()
{
	this->camera = camera::CreateFpsCamera();
	this->camera_controller = this->camera->CreateController();
}


CViewer::~CViewer()
{
}
