#include "Entity.h"
#include "Shield.h"

Entity::Entity(const Object::EnemyType::E& type, const Object::Core& core, std::vector<std::shared_ptr<Object>>& objList) :
	Object(core)
{
	switch(type)
	{
	case Object::EnemyType::Tornado:
		_falls = true;
		Text("..\\resources\\Gust.dds");
		Vel(glm::vec3(0.25, 0, 0));
		Size(glm::vec3(0.8, 1, 1));
		break;
	case Object::EnemyType::Boss:
		_falls = true;
		Text("..\\resources\\Gust.dds");
		Size(glm::vec3(3, 3, 1));
		_controller.reset(new EntityController(objList, this));
		auto bossShield = std::make_shared<Shield>(this);
		objList.push_back(bossShield);
		break;
	}
}

Entity::Entity(const glm::vec3& pos, const glm::vec3& size, const std::string& textPath, bool falls, Object::Type::E type) : 
	Object(pos, size, textPath, falls, type)
{
}

void Entity::Update(const double& secondsSinceLastUpdate, /*out*/std::vector<std::shared_ptr<Object>>& objList)
{
	if(_controller)
	{
		_controller->Update();
		_controller->ResetZones();
	}
	Object::Update(secondsSinceLastUpdate, objList);
}

void Entity::HandleCollision(Object* other)
{
	switch(other->Type())
	{
	case Object::Type::Block:
		//If we're colliding with a block, then there should be a dimension in which _prevPos wasn't colliding.
		//  Find which dimension that is, then reset _pos to match _prevPos along that axis.
		_doesXCollide = abs(Pos().x - other->Pos().x) < Size().x / 2 + other->Size().x / 2;
		_doesYCollide = abs(Pos().y - other->Pos().y) < Size().y / 2 + other->Size().y / 2;
		_doesXCollideLastFrame = abs(_prevPos.x - other->PrevPos().x) < Size().x / 2 + other->Size().x / 2;
		_doesYCollideLastFrame = abs(_prevPos.y - other->PrevPos().y) < Size().y / 2 + other->Size().y / 2;

		if(_doesXCollide && !_doesXCollideLastFrame)
		{
			_core._pos.x = _prevPos.x;
			_core._pos.y = _prevPos.y;
			_vel.y = 0;
			_vel.x = 0;
		}
		if(_doesYCollide && !_doesYCollideLastFrame)
		{
			_core._pos.y = _prevPos.y;
			_vel.y = 0;
		}
		break;
	case Object::Type::Bullet:
		if(other->OwnerType() != this->Type())
			IsAlive(false);
		break;
	case Object::Type::Enemy:
		IsAlive(false);
		break;
	}
}

void Entity::IsAlive(const bool isAlive)
{
	if(_controller)
		_controller->IsAlive(isAlive);
	Object::IsAlive(isAlive);
}