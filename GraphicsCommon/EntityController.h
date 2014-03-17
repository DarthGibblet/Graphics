#pragma once

#include "Zone.h"

#include <vector>
#include <memory>

class EntityController
{
public:
	EntityController(std::vector<std::shared_ptr<Object>>& objList, Object* parent);
	virtual ~EntityController();

	void Update();
	void ResetZones();
	void IsAlive(const bool isAlive);
protected:
	void HandlePlayerCollision(Object* player);

	std::vector<std::shared_ptr<Zone>> _zones;
	//Object that this instance is controlling. We should always be a member of
	//  this class, so we can assume that if it's deleted, we will be as well.
	//  In either case, we don't own this object, so use a raw pointer
	Object* _parent;
};