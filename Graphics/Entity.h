#pragma once

#include "Object.h"

class Entity : public Object
{
public:
	Entity(const Object::EnemyType::E& type, const Object::Core& core);
	Entity(const glm::vec3& pos, const glm::vec3& size, const std::string& textPath, bool falls, Object::Type::E type);

	virtual void HandleCollision(Object* other) override;
protected:
	bool _doesXCollide, _doesXCollideLastFrame,
		_doesYCollide, _doesYCollideLastFrame;
};