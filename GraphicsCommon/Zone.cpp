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
	if(_collisionReactions[other->Type()])
		_collisionReactions[other->Type()](other);
}

bool Zone::UsePreciseCollisions()
{
	return false;
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

void Zone::SetReactionFunc(const Object::Type::E& type, reaction_func_t reactionFunc)
{
	_collisionReactions[type] = reactionFunc;
}