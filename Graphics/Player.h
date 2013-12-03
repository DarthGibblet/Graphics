#pragma once

#include "Object.h"

#include <glm/glm.hpp>

class Player : public Object
{
public:

	Player(const glm::vec3& pos);

	virtual void Update(const double& secondsSinceLastUpdate) override;
	virtual void HandleCollision(Object* other) override;

	void JumpHold();
	void JumpRelease();
	void MoveLeft();
	void MoveRight();

protected:
	unsigned int _jumpsRemaining;
	double _jumpHoldTimer;
	bool _wallJumpable, _wallJumpLeft;
	double _wallJumpableCountdown;
	bool _movingLeft, _movingRight;
	bool _suspendFriction;

	unsigned int _upgradeMask;

};