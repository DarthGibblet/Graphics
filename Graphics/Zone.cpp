#include "Zone.h"

Zone::Zone() : Object(glm::vec3(), glm::vec3(), "", false, Object::Type::Generic)
{
	Reset();
}

void Zone::Draw()
{
}

void Zone::HandleCollision(Object* other)
{
	_currentCollisions[other->Type()] = true;
}

void Zone::Reset()
{
	for(auto i=0; i<Object::Type::END; ++i)
		_currentCollisions[i] = false;
}

bool Zone::IsColliding(const Object::Type::E& type)
{
	return _currentCollisions[type];
}