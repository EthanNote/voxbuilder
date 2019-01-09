#pragma once
#include<memory>
using namespace std;
#include "CViewer.h"
class CViewWindow
{

public:
	Viewer viewer = nullptr;
	virtual void MakeCurrent() = 0;
	virtual bool LoopCondition() = 0;
	virtual void BeforeDraw() = 0;
	virtual void AfterDraw() = 0;

	void Run();
};

typedef shared_ptr<CViewWindow> ViewWindow;


class CViewWindowFactory {
public:
	CViewWindowFactory();
	~CViewWindowFactory();
	ViewWindow Create(string title = "", int width = 800, int height = 600);
};


