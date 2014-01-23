#include "Object.h"

#include "Constants.h"

#include <GL/glew.h>

std::map<std::string, std::shared_ptr<Texture>> Object::_textureCache;

Object::Object(const glm::vec3& pos, const glm::vec3& size, const std::string& textPath, bool falls, Type::E type) : 
	_pos(pos), _size(size), _rotAxis(0, 1, 0), _rotAngle(0), _falls(falls), _type(type), _isAlive(true),
	_facingBackwards(false), _glQueryId(0)
{
	Text(textPath);
	glGenQueries(1, &_glQueryId);
}

Object::~Object()
{
	glDeleteQueries(1, &_glQueryId);
}

void Object::Update(const double& secondsSinceLastUpdate, /*out*/std::vector<std::shared_ptr<Object>>& /*objList*/)
{
	if(_falls)
	{
		_vel.y -= (float)(GRAVITY_STRENGTH * secondsSinceLastUpdate);
		if(_vel.y < -10)
			_vel.y = -10;
		//_rotAngle += secondsSinceLastUpdate * 150;
	}

	_prevPos = _pos;
	_pos += _vel * (float)secondsSinceLastUpdate;
}

void Object::Draw()
{
	auto texHolder = _text->ActivateScoped();
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
	if(Type() == Object::Type::Bullet && other->Type() == Object::Type::Bullet)
		return false;

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

			glStencilFunc(GL_ALWAYS, 1, STENCIL_BUFFER_COLLISION_DETECTION_MASK);
			glStencilOp(GL_REPLACE, GL_REPLACE, GL_REPLACE);
			Draw();

			glBeginQuery(GL_SAMPLES_PASSED, _glQueryId);
			glStencilFunc(GL_EQUAL, 1, STENCIL_BUFFER_COLLISION_DETECTION_MASK);
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

Object::Type::E Object::Type() const
{
	return _type;
}

Object::Type::E Object::OwnerType() const
{
	return Type::Generic;
}

void Object::Vel(const glm::vec3& vel)
{
	_vel = vel;
	if(_facingBackwards && _vel.x > 0)
		_facingBackwards = false;
	if(!_facingBackwards && _vel.x < 0)
		_facingBackwards = true;
}

const glm::vec3& Object::Vel() const
{
	return _vel;
}

const glm::vec3& Object::Pos() const
{
	return _pos;
}

const glm::vec3& Object::PrevPos() const
{
	return _prevPos;
}

const glm::vec3& Object::Size() const
{
	return _size;
}

void Object::IsAlive(const bool isAlive)
{
	_isAlive = isAlive;
}

bool Object::IsAlive()
{
	return _isAlive;
}

void Object::Text(const std::string& textPath)
{
	auto foundText = _textureCache.find(textPath);
	if(foundText == std::end(_textureCache))
	{
		_text = std::make_shared<Texture>(textPath);
		_textureCache[textPath] = _text;
	}
	else
	{
		_text = foundText->second;
	}
}