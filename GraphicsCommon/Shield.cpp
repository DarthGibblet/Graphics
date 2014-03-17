#include "Shield.h"

Shield::Shield(const Object* owner): Bullet(glm::vec3(), glm::vec3(), "..\\resources\\Shield.dds", owner), _owner(owner)
{
	_core._type = Object::Type::Bullet;
	Update(0, std::vector<std::shared_ptr<Object>>());
}

void Shield::Update(const double& secondsSinceLastUpdate, /*out*/std::vector<std::shared_ptr<Object>>& objList)
{
	Vel(_owner->Vel());
	glm::vec3 shieldPos = _owner->Pos();
	shieldPos.x += _facingBackwards ? -Size().x : Size().x;
	Pos(shieldPos);
	Size(_owner->Size());
}