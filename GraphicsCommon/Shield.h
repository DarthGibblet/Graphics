#pragma once

#include "Bullet.h"

class Shield : public Bullet
{
public:
	Shield(const Object* owner);

	virtual void Update(const double& secondsSinceLastUpdate, /*out*/std::vector<std::shared_ptr<Object>>& objList) override;
protected:
	const Object* _owner;
};