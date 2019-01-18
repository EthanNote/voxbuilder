#include<GL/glew.h>
#include<GLFW/glfw3.h>
#include "controller.h"
#include "camera.h"

struct MOUSE_DRAG_CONTROL {

	bool is_active;

	double dx;
	double dy;

	double _last_x;
	double _last_y;
};

struct MOUSE_DRAG_CONTROL drag_control;

void drag_init(GLFWwindow* window) {

	drag_control.is_active = true;
	drag_control.dx = 0;
	drag_control.dy = 0;
	glfwGetCursorPos(window, &drag_control._last_x, &drag_control._last_y);
}

void drag_stop() {
	drag_control.is_active = false;
	drag_control.dx = 0;
	drag_control.dy = 0;
}

void drag_update(GLFWwindow* window) {
	if (!drag_control.is_active) {
		return;
	}
	double x, y;
	glfwGetCursorPos(window, &x, &y);
	drag_control.dx = x - drag_control._last_x;
	drag_control.dy = y - drag_control._last_y;
	drag_control._last_x = x;
	drag_control._last_y = y;
}


void drag_get_vector(double *dx, double *dy) {
	*dx = drag_control.dx;
	*dy = drag_control.dy;
}

//std::shared_ptr<Controller> Controller::getptr()
//{
//	return shared_from_this();
//}

void FrameEventHandler::FrameUpdate()
{
}
#include<iostream>
void CFpsCameraController::FrameUpdate()
{
	double dx, dy;
	drag_get_vector(&dx, &dy);
	camera->yall -= dx / camera->sensitivity;
	camera->pitch -= dy / camera->sensitivity;

	float ryall = glm::radians(camera->yall);
	float rpitch = glm::radians(camera->pitch);
	glm::vec3 forward(
		-sin(ryall)*cos(rpitch),
		sin(rpitch),
		-cos(ryall)*cos(rpitch));

	glm::vec3 right(
		cos(ryall),
		0,
		-sin(ryall));

	camera->position += forward * axis.GetY() + right * axis.GetX();
}


void InputAxis::TestKey(int key, int action)
{
	for (int i = 0; i < 4; i++) {
		auto iter = std::find(stroke_keys[i].begin(), stroke_keys[i].end(), key);
		if (iter != stroke_keys[i].end()) {
			stroke_strength[i] = action;
			break;
		}
	}
}

void InputAxis::OnKeyEvent(int key, int scancode, int action, int mods)
{
	TestKey(key, action);
}

InputAxis::InputAxis()
{
	stroke_keys[UP].push_back(GLFW_KEY_W);
	stroke_keys[UP].push_back(GLFW_KEY_UP);

	stroke_keys[DOWN].push_back(GLFW_KEY_S);
	stroke_keys[DOWN].push_back(GLFW_KEY_DOWN);

	stroke_keys[LEFT].push_back(GLFW_KEY_A);
	stroke_keys[LEFT].push_back(GLFW_KEY_LEFT);

	stroke_keys[RIGHT].push_back(GLFW_KEY_D);
	stroke_keys[RIGHT].push_back(GLFW_KEY_RIGHT);
}
	
float InputAxis::GetX()
{
	auto v = stroke_strength[RIGHT] - stroke_strength[LEFT];
	if (v > 1) { v = 1; }
	if (v < -1) { v = -1; }
	return v;
}

float InputAxis::GetY()
{
	auto v = stroke_strength[UP] - stroke_strength[DOWN];
	if (v > 1) { v = 1; }
	if (v < -1) { v = -1; }
	return v;
}

#include<list>
std::list<KeyEventHandler*> keyevent_handlers;
std::list<MousePositionEventHandler*> mousepos_handlers;

void _keyevent_handler_call(int key, int scancode, int action, int mods) {
	for (auto i = keyevent_handlers.begin(); i != keyevent_handlers.end(); i++) {
		(*i)->OnKeyEvent(key, scancode, action, mods);
	}
}

void _mousepos_handler_call(double x, double y)
{
	for (auto i = mousepos_handlers.begin(); i != mousepos_handlers.end(); i++) {
		(*i)->OnMousePosition(x, y);
	}
}

void _key_callback(GLFWwindow*, int key, int scancode, int action, int mods) {
	_keyevent_handler_call(key, scancode, action, mods);
}

void _cursorpos_callback(GLFWwindow*, double x, double y) {
	_mousepos_handler_call(x, y);
}
//void KeyEventHandler::Enable()
//{
//	/*GLFWkeyfun(keyfunc);
//	std::cout << "???"<<std::endl;*/
//	//glfwSetKeyCallback()
//}

KeyEventHandler::KeyEventHandler()
{
	keyevent_handlers.push_back(this);

}

KeyEventHandler::~KeyEventHandler()
{
	keyevent_handlers.remove(this);
}

void COrbitCameraController::FrameUpdate()
{
	if (!this->camera->enable_rotate) {
		return;
	}
	double dx, dy;
	drag_get_vector(&dx, &dy);
	camera->yall -= dx / camera->sensitivity;
	camera->pitch -= dy / camera->sensitivity;

	if (!move_enable) {
		return;
	}

	float ryall = glm::radians(camera->yall);
	float rpitch = glm::radians(camera->pitch);
	glm::vec3 forward(
		-sin(ryall)*cos(rpitch),
		sin(rpitch),
		-cos(ryall)*cos(rpitch));

	glm::vec3 right(
		cos(ryall),
		0,
		-sin(ryall));

	camera->center += forward * axis.GetY() + right * axis.GetX();
}

void COrbitCameraController::OnKeyEvent(int key, int scancode, int action, int mods)
{
	if (key == GLFW_KEY_LEFT_ALT) {
		this->camera->enable_rotate = action;
	}
}

MousePositionEventHandler::MousePositionEventHandler()
{
	mousepos_handlers.push_back(this);
}

MousePositionEventHandler::~MousePositionEventHandler()
{
	mousepos_handlers.remove(this);
}
