#include "Object.h"

#include <GL/glew.h>

Object::Object(const glm::vec3& pos, const glm::vec3& size, const std::string& texPath, bool falls) : 
	_pos(pos), _size(size), _rotAxis(0, 1, 0), _rotAngle(0), _falls(falls), _tex(texPath)
{
}

void Object::Update(const double& secondsSinceLastUpdate)
{
	if(_falls)
	{
		_vel.y -= (float)(0.5 * secondsSinceLastUpdate);
		//_rotAngle += secondsSinceLastUpdate * 150;
	}

	_prevPos = _pos;
	_pos += _vel * (float)secondsSinceLastUpdate;
}

void Object::Draw()
{
	auto texHolder = _tex.ActivateScoped();
	glPushMatrix();
	glTranslatef(_pos.x, _pos.y, _pos.z);
	glRotatef((float)_rotAngle, _rotAxis.x, _rotAxis.y, _rotAxis.z);
	glScalef(_size.x, _size.y, _size.z);
	_mesh.Draw();
	glPopMatrix();
}

bool Object::DoesCollide(std::shared_ptr<Object> other)
{
	return DoesCollide(other.get());
}

bool Object::DoesCollide(Object* other)
{
	if(abs(_pos.x - other->_pos.x) < _size.x / 2 + other->_size.x / 2)
		if(abs(_pos.y - other->_pos.y) < _size.y / 2 + other->_size.y / 2)
			return true;
	return false;
}

void Object::HandleCollision(std::shared_ptr<Object> other)
{
	HandleCollision(other.get());
}

void Object::HandleCollision(Object* other)
{
	_pos = _prevPos;
	_vel = glm::vec3(0, 0, 0);
}

bool Object::IsContainedByBox(const glm::vec3& boxCenter, const double& boxWidth, const double& boxHeight)
{
	if(	_pos.x - _size.x / 2 >= boxCenter.x - boxWidth / 2 &&
		_pos.x + _size.x / 2 <= boxCenter.x + boxWidth / 2 &&
		_pos.y - _size.y / 2 >= boxCenter.y - boxHeight / 2 &&
		_pos.y + _size.y / 2 <= boxCenter.y + boxHeight / 2)
		return true;
	return false;
}