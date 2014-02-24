#pragma once

#include "Object.h"

class Zone : public Object
{
public:
	Zone();

	virtual void Draw() override;

	virtual void HandleCollision(Object* other) override;

	void Reset();
	bool IsColliding(const Object::Type::E& type);
protected:
	bool _currentCollisions[Object::Type::END];
};