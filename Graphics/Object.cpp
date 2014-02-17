#include "Object.h"

#include "Constants.h"

#include <GL/glew.h>

std::map<std::string, std::shared_ptr<Texture>> Object::_textureCache;

Object::Core::Core() :
	_type(Object::Type::Generic), _pos(0, 0, 0), _size(1, 1, 1), _vel(0, 0, 0)
{
}

Object::Core::Core(const Object::Type::E& type, const glm::vec3& pos, const glm::vec3& size) :
	_type(type), _pos(pos), _size(size)
{
}

bool Object::Core::StreamInsert(std::ofstream& stream) const
{
	bool rv = true;
	rv &= DataFile::Insert(stream, _type);
	rv &= DataFile::Insert(stream, _pos);
	rv &= DataFile::Insert(stream, _size);
	return rv;
}

bool Object::Core::StreamExtract(std::ifstream& stream)
{
	bool rv = true;
	rv &= DataFile::Extract(stream, _type);
	rv &= DataFile::Extract(stream, _pos);
	rv &= DataFile::Extract(stream, _size);
	return rv;
}

Object::Object() : _rotAxis(0, 1, 0), _rotAngle(0), _falls(false), _isAlive(true),
	_facingBackwards(false), _glQueryId(0)
{
	Text("");
	glGenQueries(1, &_glQueryId);
}

Object::Object(const Object::Core& core) : _core(core), _rotAxis(0, 1, 0), _rotAngle(0), _falls(false), _isAlive(true),
	_facingBackwards(false), _glQueryId(0)
{
	Text("");
	glGenQueries(1, &_glQueryId);
}

Object::Object(const glm::vec3& pos, const glm::vec3& size, const std::string& textPath, bool falls, Type::E type) : 
	_core(type, pos, size), _rotAxis(0, 1, 0), _rotAngle(0), _falls(falls), _isAlive(true),
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

	_prevPos = Pos();
	_core._pos += _vel * (float)secondsSinceLastUpdate;
}

void Object::Draw()
{
	auto texHolder = _text->ActivateScoped();
	glPushMatrix();
	glTranslatef(Pos().x, Pos().y, Pos().z);
	glRotatef((float)_rotAngle, _rotAxis.x, _rotAxis.y, _rotAxis.z);
	glScalef(Size().x, Size().y, Size().z);
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

	if(abs(Pos().x - other->Pos().x) < Size().x / 2 + other->Size().x / 2)
	{
		if(abs(Pos().y - other->Pos().y) < Size().y / 2 + other->Size().y / 2)
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
	switch(Type())
	{
	case Type::Block:
		break;
	case Type::Enemy:
		switch(other->Type())
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
	if(	Pos().x - Size().x / 2 >= boxCenter.x - boxWidth / 2 &&
		Pos().x + Size().x / 2 <= boxCenter.x + boxWidth / 2 &&
		Pos().y - Size().y / 2 >= boxCenter.y - boxHeight / 2 &&
		Pos().y + Size().y / 2 <= boxCenter.y + boxHeight / 2)
		return true;
	return false;
}

bool Object::UsePreciseCollisions()
{
	return Type() != Type::Block;
}

Object::Type::E Object::Type() const
{
	return _core._type;
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
	return _core._pos;
}

void Object::Pos(const glm::vec3& pos)
{
	_core._pos = pos;
}

const glm::vec3& Object::PrevPos() const
{
	return _prevPos;
}

const glm::vec3& Object::Size() const
{
	return _core._size;
}

void Object::Size(const glm::vec3& size)
{
	_core._size = size;
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

bool Object::StreamInsert(std::ofstream& stream) const
{
	return DataFile::Insert(stream, _core);
}

bool Object::StreamExtract(std::ifstream& stream)
{
	return DataFile::Extract(stream, _core);
}