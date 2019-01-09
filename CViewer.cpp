#include "CViewer.h"



void CViewer::Draw()
{
}

CViewer::CViewer()
{
	this->camera = camera::CreateFpsCamera();
	this->camera_controller = this->camera->CreateController();
}


CViewer::~CViewer()
{
}
