
#include"CViewWindow.h"
#pragma comment(lib, "opengl32.lib")
int main() {
	CViewWindowFactory factory;
	
	auto window = factory.Create();
	window->viewer = Viewer(new CViewer);
	window->Run();

}