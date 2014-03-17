#pragma once

#include "Object.h"
#include "EntityController.h"

#include <memory>

class Entity : public Object
{
public:
	Entity(const Object::EnemyType::E& type, const Object::Core& core, std::vector<std::shared_ptr<Object>>& objList);
	Entity(const glm::vec3& pos, const glm::vec3& size, const std::string& textPath, bool falls, Object::Type::E type);

	void Update(const double& secondsSinceLastUpdate, /*out*/std::vector<std::shared_ptr<Object>>&objList) override;
	void IsAlive(const bool isAlive) override;
	using Object::IsAlive;

	virtual void HandleCollision(Object* other) override;
protected:
	bool _doesXCollide, _doesXCollideLastFrame,
		_doesYCollide, _doesYCollideLastFrame;
	std::unique_ptr<EntityController> _controller;
};