#include "EntityController.h"

EntityController::EntityController(std::vector<std::shared_ptr<Object>>& objList, Object* parent) : _parent(parent)
{
	auto chaseZone = std::make_shared<Zone>();
	chaseZone->Size(glm::vec3(15, 20, 0));
	chaseZone->SetReactionFunc(Object::Type::Player, std::bind(&EntityController::HandlePlayerCollision, this, std::placeholders::_1));
	_zones.push_back(chaseZone);
	objList.push_back(chaseZone);
}

EntityController::~EntityController()
{
	//In the case that we're destroyed before being marked as dead, make sure all child objects are cleaned up correctly
	IsAlive(false);
}

void EntityController::Update()
{
	//Make all the detection zones stay centered on the parent object
	foreach(_zones, [this](decltype(*_zones.begin()) zone)
	{
		if(_parent)
			zone->Pos(_parent->Pos());
	});

	if(_zones.size() > 0)
	{
		if(!_zones[0]->IsColliding(Object::Type::Player) && _parent)
		{
			auto newVel = _parent->Vel();
			newVel.x = 0;
			_parent->Vel(newVel);
		}
	}
}

void EntityController::ResetZones()
{
	foreach(_zones, [](decltype(*_zones.cbegin()) zone)
	{
		zone->Reset();
	});
}

void EntityController::IsAlive(const bool isAlive)
{
	foreach(_zones, [&isAlive](decltype(*std::begin(_zones)) zone)
	{
		zone->IsAlive(isAlive);
	});
}

void EntityController::HandlePlayerCollision(Object* player)
{
	if(_parent)
	{
		auto newVel = _parent->Vel();
		if(_parent->Pos().x < player->Pos().x)
			newVel.x = 0.5;
		else
			newVel.x = -0.5;
		_parent->Vel(newVel);
	}
}