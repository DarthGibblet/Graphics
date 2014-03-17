#pragma once

#include "Bullet.h"

class Slash : public Bullet
{
public:
	Slash(const glm::vec3& relativePos, const std::string& textPath, const Object* owner, const glm::vec3& size);

	virtual void Update(const double& secondsSinceLastUpdate, /*out*/std::vector<std::shared_ptr<Object>>& objList) override;

	void RelativePos(const glm::vec3& relativePos);
protected:
	glm::vec3 _relativePos;
	//Object that this instance is tied to. We should be a member of this object, so
	//  we can assume the object won't get deleted out from under us.
	//  In either case, we don't own this instance, so use a raw pointer.
	const Object* _owner;
};