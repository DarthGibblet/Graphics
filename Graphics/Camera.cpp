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
		_pos = _followedObj->Pos();

	if(_pos.x - _maxX < _restrictLeft)
		_pos.x = static_cast<float>(_restrictLeft + _maxX);
	if(_pos.x + _maxX > _restrictRight)
		_pos.x = static_cast<float>(_restrictRight - _maxX);
	if(_pos.y + _maxY > _restrictTop)
		_pos.y = static_cast<float>(_restrictTop - _maxY);
	if(_pos.y - _maxY < _restrictBottom)
		_pos.y = static_cast<float>(_restrictBottom + _maxY);
}

void Camera::Draw()
{
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-_maxX, _maxX, -_maxY, _maxY, 10, -10);
	glTranslated(-_pos.x, -_pos.y, -_pos.z);
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