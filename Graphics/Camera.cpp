#include "Camera.h"

Camera::Camera(const double& maxX, const double& ratio) : 
	Object(glm::vec3(0, 0, 0), glm::vec3(0, 0, 0), std::string(), false, Object::Type::Camera), 
	_maxX(maxX), _maxY(_maxX * ratio), _followedObj(nullptr), _restrictLeft(-_maxX), _restrictRight(_maxX),
	_restrictTop(_maxY), _restrictBottom(-_maxY)
{
}

void Camera::Update(const double& secondsSinceLastFrame, /*out*/std::vector<std::shared_ptr<Object>>& /*objList*/)
{
	if(_followedObj)
		Pos(_followedObj->Pos());

	if(Pos().x - _maxX < _restrictLeft)
		_core._pos.x = static_cast<float>(_restrictLeft + _maxX);
	if(Pos().x + _maxX > _restrictRight)
		_core._pos.x = static_cast<float>(_restrictRight - _maxX);
	if(Pos().y + _maxY > _restrictTop)
		_core._pos.y = static_cast<float>(_restrictTop - _maxY);
	if(Pos().y - _maxY < _restrictBottom)
		_core._pos.y = static_cast<float>(_restrictBottom + _maxY);
}

void Camera::Draw()
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-_maxX, _maxX, -_maxY, _maxY, 10, -10);
	glTranslated(-Pos().x, -Pos().y, -Pos().z);
}

void Camera::Teather(Object* followedObj)
{
	_followedObj = followedObj;
}

void Camera::SetRestrictLeft(const double& restrictLeft)
{
	_restrictLeft = restrictLeft;
}

void Camera::SetRestrictRight(const double& restrictRight)
{
	_restrictRight = restrictRight;
}

void Camera::SetRestrictTop(const double& restrictTop)
{
	_restrictTop = restrictTop;
}

void Camera::SetRestrictBottom(const double& restrictBottom)
{
	_restrictBottom = restrictBottom;
}