#pragma once

#include "Object.h"

class Bullet : public Object
{
public:
	Bullet(const glm::vec3& pos, const glm::vec3& vel, const std::string& texPath, const Object* owner, const glm::vec3& size = glm::vec3(0.25, 0.25, 0.25));

	virtual void HandleCollision(Object* other) override;
protected:
	const Object* _owner;
};