#pragma once

#include "Object.h"

#include <functional>

class Zone : public Object
{
public:
	typedef std::function<void(Object*)> reaction_func_t;

	Zone();

	virtual void Draw() override;

	virtual void HandleCollision(Object* other) override;
	virtual bool UsePreciseCollisions() override;

	void Reset();
	bool IsColliding(const Object::Type::E& type);
	void SetReactionFunc(const Object::Type::E& type, reaction_func_t reactionFunc);
protected:
	bool _currentCollisions[Object::Type::END];
	reaction_func_t _collisionReactions[Object::Type::END];

};