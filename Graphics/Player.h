#pragma once

#include "Object.h"
#include "Bullet.h"

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
	std::shared_ptr<Bullet> Fire();

protected:
	unsigned int _jumpsRemaining;
	double _jumpHoldTimer;
	bool _isJumping, _wallJumpable, _wallJumpLeft;
	glm::vec3 _curJumpVel;
	double _wallJumpableCountdown;
	bool _movingLeft, _movingRight;
	bool _suspendFriction;

	unsigned int _upgradeMask;

};