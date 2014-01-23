#pragma once

#include "Object.h"

class Bullet : public Object
{
public:
	Bullet(const glm::vec3& pos, const glm::vec3& vel, const std::string& textPath, const Object* owner, const glm::vec3& size = glm::vec3(0.25, 0.25, 0.25));

	virtual void Update(const double& secondsSinceLastUpdate, /*out*/std::vector<std::shared_ptr<Object>>& objList) override;
	virtual void HandleCollision(Object* other) override;
	virtual Object::Type::E OwnerType() const override;

	void SetBounds(const double& minX, const double& maxX, const double& minY, const double& maxY);
protected:
	const Object::Type::E _ownerType;
	double _minX, _maxX, _minY, _maxY;
};