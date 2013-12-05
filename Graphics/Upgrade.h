#pragma once

#include "Object.h"

class Upgrade : public Object
{
public:
	struct Type
	{
		enum E { WALL_JUMP = 1, DOUBLE_JUMP = 2 };
	};

	Upgrade(const glm::vec3& pos, const glm::vec3& size, const std::string& textPath, Upgrade::Type::E power);

	virtual void HandleCollision(Object* other) override;

	Type::E Power();

protected:
	Type::E _power;
};