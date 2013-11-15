#include "Object.h"

#include <GL/glew.h>

Object::Object(const glm::vec3& pos, const glm::vec3& size, const std::string& texPath) : _pos(pos), _size(size), _rotAxis(0, 1, 0), _rotAngle(0), _tex(texPath)
{
}

void Object::Update(const double& secondsSinceLastUpdate)
{
	_rotAngle += secondsSinceLastUpdate * 150;
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