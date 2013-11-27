#include "Object.h"

#include <GL/glew.h>

Object::Object(const glm::vec3& pos, const glm::vec3& size, const std::string& texPath, bool falls, Type::E type) : 
	_pos(pos), _size(size), _rotAxis(0, 1, 0), _rotAngle(0), _falls(falls), _type(type), _isAlive(true),
	_facingBackwards(false), _tex(texPath), _glQueryId(0)
{
	glGenQueries(1, &_glQueryId);
}

Object::~Object()
{
	glDeleteQueries(1, &_glQueryId);
}

void Object::Update(const double& secondsSinceLastUpdate)
{
	if(_falls)
	{
		_vel.y -= (float)(0.5 * secondsSinceLastUpdate);
		//_rotAngle += secondsSinceLastUpdate * 150;
	}

	if(_facingBackwards && _vel.x > 0)
		_facingBackwards = false;
	if(!_facingBackwards && _vel.x < 0)
		_facingBackwards = true;

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
	_mesh.Draw(_facingBackwards);
	glPopMatrix();
}

bool Object::DoesCollide(std::shared_ptr<Object> other)
{
	return DoesCollide(other.get());
}

bool Object::DoesCollide(Object* other)
{
	if(abs(_pos.x - other->_pos.x) < _size.x / 2 + other->_size.x / 2)
	{
		if(abs(_pos.y - other->_pos.y) < _size.y / 2 + other->_size.y / 2)
		{
			//Sometimes (eg when colliding with the envoronment), we don't want pixel-perfect collisions. In that case, 
			//  just having the bounding boxes collide is enough
			if(!UsePreciseCollisions() || !other->UsePreciseCollisions())
				return true;

			glPushAttrib(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_ENABLE_BIT | GL_POLYGON_BIT | GL_STENCIL_BUFFER_BIT);
			glColorMask(GL_FALSE, GL_FALSE, GL_FALSE, GL_FALSE);
			glDisable(GL_LIGHTING);
			glDepthMask(GL_FALSE);
			glEnable(GL_STENCIL_TEST);

			glStencilFunc(GL_ALWAYS, 1, 1);
			glStencilOp(GL_REPLACE, GL_REPLACE, GL_REPLACE);
			Draw();

			glBeginQuery(GL_SAMPLES_PASSED, _glQueryId);
			glStencilFunc(GL_EQUAL, 1, 1);
			glStencilOp(GL_KEEP, GL_KEEP, GL_KEEP);
			other->Draw();

			glEndQuery(GL_SAMPLES_PASSED);
			GLint resultCount = 0;

			glGetQueryObjectiv(_glQueryId, GL_QUERY_RESULT, &resultCount);

			glClear(GL_STENCIL_BUFFER_BIT);
			glPopAttrib();
			//if(_type != Type::Block && other->Type() != Type::Block)
			//	std::cout <<"Collision of " <<resultCount <<" pixels." <<std::endl;
			return resultCount >= 10;
		}
	}
	return false;
}

void Object::HandleCollision(std::shared_ptr<Object> other)
{
	this->HandleCollision(other.get());
}

void Object::HandleCollision(Object* other)
{
	switch(_type)
	{
	case Type::Block:
		break;
	case Type::Player:
		switch(other->_type)
		{
		case Type::Block:
			{
				//If we're colliding with a block, then there should be a dimension in which _prevPos wasn't colliding.
				//  Find which dimension that is, then reset _pos to match _prevPos along that axis.
				auto doesXCollide = abs(_pos.x - other->_pos.x) < _size.x / 2 + other->_size.x / 2;
				auto doesYCollide = abs(_pos.y - other->_pos.y) < _size.y / 2 + other->_size.y / 2;
				auto doesXCollideLastFrame = abs(_prevPos.x - other->_prevPos.x) < _size.x / 2 + other->_size.x / 2;
				auto doesYCollideLastFrame = abs(_prevPos.y - other->_prevPos.y) < _size.y / 2 + other->_size.y / 2;

				if(doesXCollide && !doesXCollideLastFrame)
				{
					_pos.x = _prevPos.x;
					_vel.x = 0;
				}
				if(doesYCollide && !doesYCollideLastFrame)
				{
					_pos.y = _prevPos.y;
					_vel.y = 0;
				}
			}
			break;
		case Type::Bullet:
			break;
		case Type::Enemy:
			//_isAlive = false;
			break;
		}
		break;
	case Type::Enemy:
		switch(other->_type)
		{
		case Type::Bullet:
			//_isAlive = false;
			break;
		}
		break;
	}
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

bool Object::UsePreciseCollisions()
{
	return _type != Type::Block;
}

Object::Type::E Object::Type()
{
	return _type;
}

void Object::Vel(const glm::vec3& vel)
{
	_vel = vel;
}

glm::vec3& Object::Vel()
{
	return _vel;
}

glm::vec3& Object::Pos()
{
	return _pos;
}

bool Object::IsAlive()
{
	return _isAlive;
}