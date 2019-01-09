#pragma once

#include "CVoxBuffer.h"
#include "camera.h"
#include "controller.h"
class CViewer
{
	shared_ptr<FrameEventHandler> camera_controller;
public:

	VoxBuffer buffer;
	FpsCamera camera;
	void Draw();

	CViewer();
	~CViewer();
};


typedef shared_ptr<CViewer> Viewer;
