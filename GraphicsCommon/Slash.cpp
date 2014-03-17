#include "Slash.h"

Slash::Slash(const glm::vec3& relativePos, const std::string& textPath, const Object* owner, const glm::vec3& size) :
	Bullet(owner ? owner->Pos() + relativePos : glm::vec3(0, 0, 0), glm::vec3(0, 0, 0), textPath, owner, size), _relativePos(relativePos), _owner(owner)
{
}

void Slash::Update(const double& secondsSinceLastUpdate, /*out*/std::vector<std::shared_ptr<Object>>& objList)
{
	Pos((_owner ? _owner->Pos() : glm::vec3(0, 0, 0)) + _relativePos);
	Bullet::Update(secondsSinceLastUpdate, objList);
}

void Slash::RelativePos(const glm::vec3& relativePos)
{
	_relativePos = relativePos;
}