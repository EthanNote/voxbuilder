#ifndef _CONTROLLER_H_
#define _CONTROLLER_H_

#include<memory>
#include<vector>

class CCamera;

class KeyEventHandler {
	friend void _handler_call(int key, int scancode, int action, int mods);
protected:
	virtual void OnKeyEvent(int key, int scancode, int action, int mods) = 0;
public:
	KeyEventHandler();
	~KeyEventHandler();
};

class InputAxis:public KeyEventHandler {
	enum {UP=0, DOWN = 1, RIGHT = 2, LEFT = 3};
	float stroke_strength[4];
	std::vector<int> stroke_keys[4];
	void TestKey(int key, int action);
	void OnKeyEvent(int key, int scancode, int action, int mods) override;
public:
	InputAxis();
	float GetX();
	float GetY();
};

class FrameEventHandler {
public:
	virtual void FrameUpdate();
};

//class CameraController : public Controller {
//public:
//	std::shared_ptr<CCamera> camera;
//};


class CFpsCameraController : public FrameEventHandler {
	friend class CFpsCamera;
	CFpsCamera* camera;
	InputAxis axis;
	virtual void FrameUpdate() override;
};



#endif // !_CONTROLLER_H_