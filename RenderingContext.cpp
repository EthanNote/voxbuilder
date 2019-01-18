#include<GL/glew.h>
#include<GLFW/glfw3.h>
#include<iostream>
#include "RenderingContext.h"
#include<map>

#pragma comment(lib, "opengl32.lib")

class OpenGLRenderingContext :public RenderingContext
{
	GLFWwindow* window;
public:
	void Run() override;
	OpenGLRenderingContext(int width, int height, const char* title);
	~OpenGLRenderingContext();
};


extern void drag_update(GLFWwindow* window);

void OpenGLRenderingContext::Run()
{
	//auto window = ((OpenGLRenderWindow*)this->window)->window;
	while (!glfwWindowShouldClose(window))
	{
		drag_update(window);
		/* Render here */
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		if (pipline) {
			pipline->Draw();
		}
		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();
	}
}

extern void drag_init(GLFWwindow* window);
extern void _key_callback(GLFWwindow*, int key, int scancode, int action, int mods);
extern void _cursorpos_callback(GLFWwindow*, double x, double y);

OpenGLRenderingContext::OpenGLRenderingContext(int width, int height, const char* title )
{
	
	if (!glfwInit()) {
		fprintf(stderr, "ERROR: could not start GLFW3\n");
		return;
	}

	window = glfwCreateWindow(width, height, title, NULL, NULL);
	if (!window) {
		fprintf(stderr, "ERROR: could not open window with GLFW3\n");
		glfwTerminate();
		return;
	}

	glfwMakeContextCurrent(window);

	drag_init(window);
	glfwSetKeyCallback(window, _key_callback);
	glfwSetCursorPosCallback(window, _cursorpos_callback);
	glfwSetWindowSizeCallback(window, NULL);

	// start GLEW extension handler
	glewExperimental = GL_TRUE;
	GLenum err = glewInit();
	if (GLEW_OK != err)
	{
		/* Problem: glewInit failed, something is seriously wrong. */
		fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
		return;
	}
	fprintf(stdout, "Status: Using GLEW %s\n", glewGetString(GLEW_VERSION));

	// tell GL to only draw onto a pixel if the shape is closer to the viewer
	glEnable(GL_DEPTH_TEST); // enable depth-testing
	glDepthFunc(GL_LESS); // depth-testing interprets a smaller value as "closer"
	

}


OpenGLRenderingContext::~OpenGLRenderingContext()
{
}

RenderingContext * RenderingContextFactory::CreateGLFWContext(int width, int height, const char* title)
{
	return new OpenGLRenderingContext(width, height, title);
}
