#include<memory>
#include "camera.h"
#include "controller.h"

std::shared_ptr<CCamera> CCamera::current_attached_camera = nullptr;

glm::mat4 & CCamera::GetProjection()
{
	this->_last_get_projection =
		glm::perspective(
			glm::radians(this->m_perspectiveInfo.fov),
			this->m_perspectiveInfo.aspect,
			this->m_perspectiveInfo.zNear,
			this->m_perspectiveInfo.zFar);

	return this->_last_get_projection;
}

glm::mat4 & CCamera::GetModelView()
{
	return this->_last_get_modelview;
}

glm::mat4 & CCamera::GetView()
{
	return this->_last_get_view;
	// TODO: 在此处插入 return 语句
}

glm::mat4 & CCamera::GetModel()
{
	return this->_last_get_model;
	// TODO: 在此处插入 return 语句
}

glm::mat4 & CCamera::GetMVP()
{
	this->_last_get_mvp = this->GetProjection() * this->GetModelView();
	return this->_last_get_mvp;
}


void CCamera::setupControls()
{
}



std::shared_ptr<FrameEventHandler> CCamera::CreateController()
{
	auto controller = std::shared_ptr<FrameEventHandler>(new FrameEventHandler());
	return controller;
}

CCamera::CCamera()
{
}


glm::mat4 & CFpsCamera::GetView()
{
	float ryall = glm::radians(this->yall);
	float rpitch = glm::radians(this->pitch);
	glm::vec3 looktarget(
		-sin(ryall)*cos(rpitch),
		sin(rpitch),
		-cos(ryall)*cos(rpitch));
	auto view = glm::lookAt(glm::vec3(0), looktarget, glm::vec3(0, 1, 0));
	this->_last_get_view = view;

	return _last_get_view;
}

glm::mat4 & CFpsCamera::GetModel()
{
	glm::translate(_last_get_model, -this->position);
	return this->_last_get_model;
}

glm::mat4 & CFpsCamera::GetModelView()
{
	float ryall = glm::radians(this->yall);
	float rpitch = glm::radians(this->pitch);
	glm::vec3 looktarget(
		-sin(ryall)*cos(rpitch) + this->position.x,
		sin(rpitch) + this->position.y,
		-cos(ryall)*cos(rpitch) + this->position.z);
	auto mv = glm::lookAt(this->position, looktarget, glm::vec3(0, 1, 0));
	this->_last_get_modelview = mv;

	return _last_get_modelview;
}

std::shared_ptr<FrameEventHandler> CFpsCamera::CreateController()
{
	auto controller = std::shared_ptr<CFpsCameraController>(new CFpsCameraController);
	controller->camera = this;

	return std::static_pointer_cast<FrameEventHandler>(controller);
}



PerspectiveInfo::PerspectiveInfo()
{
	this->fov = 60;
	this->aspect = 1.33;
	this->zFar = 1000;
	this->zNear = 0.1;
}

FpsCamera camera::CreateFpsCamera()
{
	return FpsCamera(new CFpsCamera);
}

OrbitCamera camera::CreateOrbitCamera()
{
	return OrbitCamera(new COrbitCamera);
}

glm::mat4 & COrbitCamera::GetView()
{
	float ryall = glm::radians(this->yall);
	float rpitch = glm::radians(this->pitch);
	glm::vec3 eyepos(
		-sin(ryall)*cos(rpitch)*radius+center.x,
		sin(rpitch)*radius + center.y,
		-cos(ryall)*cos(rpitch)*radius + center.z);
	auto view = glm::lookAt(eyepos, center, glm::vec3(0, 1, 0));
	this->_last_get_view = view;

	return _last_get_view;
	// TODO: 在此处插入 return 语句
}

glm::mat4 & COrbitCamera::GetModel()
{
	glm::translate(_last_get_model, -this->center);
	return this->_last_get_model;
	// TODO: 在此处插入 return 语句
}

glm::mat4 & COrbitCamera::GetModelView()
{
	/*float ryall = glm::radians(this->yall);
	float rpitch = glm::radians(this->pitch);
	glm::vec3 looktarget(
		-sin(ryall)*cos(rpitch) + this->center.x,
		sin(rpitch) + this->center.y,
		-cos(ryall)*cos(rpitch) + this->center.z);
	auto mv = glm::lookAt(this->center, looktarget, glm::vec3(0, 1, 0));
	this->_last_get_modelview = mv;*/

	GetModel();
	GetView();

	_last_get_modelview = _last_get_view * _last_get_model;

	return _last_get_modelview;
	// TODO: 在此处插入 return 语句
}

std::shared_ptr<FrameEventHandler> COrbitCamera::CreateController()
{
	auto controller = std::shared_ptr<COrbitCameraController>(new COrbitCameraController);
	controller->camera = this;

	return std::static_pointer_cast<FrameEventHandler>(controller);
	//return std::shared_ptr<FrameEventHandler>();
}
