#include "Entity.h"

Entity::Entity(const glm::vec3& pos, const glm::vec3& size, const std::string& textPath, bool falls, Type::E type) : 
	Object(pos, size, textPath, falls, type)
{
}

void Entity::HandleCollision(Object* other)
{
	switch(other->Type())
	{
	case Type::Block:
		//If we're colliding with a block, then there should be a dimension in which _prevPos wasn't colliding.
		//  Find which dimension that is, then reset _pos to match _prevPos along that axis.
		_doesXCollide = abs(_pos.x - other->Pos().x) < _size.x / 2 + other->Size().x / 2;
		_doesYCollide = abs(_pos.y - other->Pos().y) < _size.y / 2 + other->Size().y / 2;
		_doesXCollideLastFrame = abs(_prevPos.x - other->PrevPos().x) < _size.x / 2 + other->Size().x / 2;
		_doesYCollideLastFrame = abs(_prevPos.y - other->PrevPos().y) < _size.y / 2 + other->Size().y / 2;

		if(_doesXCollide && !_doesXCollideLastFrame)
		{
			_pos.x = _prevPos.x;
			_pos.y = _prevPos.y;
			_vel.y = 0;
			_vel.x = 0;
		}
		if(_doesYCollide && !_doesYCollideLastFrame)
		{
			_pos.y = _prevPos.y;
			_vel.y = 0;
		}
		break;
	case Type::Bullet:
		if(other->OwnerType() != Type())
			_isAlive = false;
		break;
	case Type::Enemy:
		_isAlive = false;
		break;
	}
}