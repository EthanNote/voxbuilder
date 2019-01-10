#pragma once
#include"Pipline.h"

class RenderingContext {
public:
	Pipline* pipline=NULL;

	virtual void Run()=0;
};



class RenderingContextFactory {
public:
	RenderingContext* CreateGLFWContext(int width = 800, int height = 600, const char* title = "GLFW");
	
};