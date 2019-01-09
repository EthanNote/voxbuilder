#include<GL/glew.h>
#include <GLFW/glfw3.h>
#include<iostream>
#include "CViewWindow.h"



CViewWindowFactory::CViewWindowFactory()
{
	glewInit();

	if (!glfwInit()) {
		cout << "cannot init glfw" << endl;
	}
}

CViewWindowFactory::~CViewWindowFactory()
{
	glfwTerminate();
}


class COpenGLViewWindow : public CViewWindow {
public:
	GLFWwindow* window;
	void MakeCurrent() override;
	bool LoopCondition() override;
	virtual void BeforeDraw() override;
	virtual void AfterDraw() override;
};

extern void _key_callback(GLFWwindow*, int, int, int, int);

ViewWindow CViewWindowFactory::Create(string title , int width , int height)
{
	auto p_view_window = new COpenGLViewWindow;
	p_view_window->window = glfwCreateWindow(width, height, title.c_str(), NULL, NULL);
	if (!p_view_window->window)
	{
		glfwTerminate();
		cout << "cannot create window" << endl;
		delete p_view_window;
	}
	glfwSetKeyCallback(p_view_window->window, _key_callback);
	return ViewWindow(p_view_window);
}

void COpenGLViewWindow::MakeCurrent()
{
	glfwMakeContextCurrent(window);
}

bool COpenGLViewWindow::LoopCondition()
{
	if (glfwWindowShouldClose(window)) {
		return false;
	}
	return true;
}

void COpenGLViewWindow::BeforeDraw()
{
	glClear(GL_COLOR_BUFFER_BIT);
}

void COpenGLViewWindow::AfterDraw()
{
	/* Swap front and back buffers */
	glfwSwapBuffers(window);

	/* Poll for and process events */
	glfwPollEvents();
}

void CViewWindow::Run()
{
	while (LoopCondition()) {
		BeforeDraw();
		if (viewer) {
			viewer->Draw();
		}
		AfterDraw();
	}
}
