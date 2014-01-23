#pragma once

#include "Entity.h"
#include "Bullet.h"
#include "Upgrade.h"
#include "Shield.h"

#include <glm/glm.hpp>

#include <memory>

class Player : public Entity
{
public:

	Player(const glm::vec3& pos, const unsigned int upgradeMask);

	virtual void Update(const double& secondsSinceLastUpdate, /*out*/std::vector<std::shared_ptr<Object>>& objList) override;
	virtual void HandleCollision(Object* other) override;

	void JumpHold();
	void JumpRelease();
	void CrouchHold();
	void CrouchRelease();
	void MoveLeft();
	void MoveRight();
	std::shared_ptr<Bullet> Fire();

	unsigned int GetUpgradeMask() const;
	bool HasUpgrade(const Upgrade::Type::E& upgrade) const;

protected:
	unsigned int _jumpsRemaining;
	double _jumpHoldTimer;
	bool _isJumping, _wallJumpable, _wallJumpLeft;
	double _dashTimer;
	bool _crouching, _dashReady, _dashing, _pendingCrouchRelease;
	glm::vec3 _curJumpVel;
	double _wallJumpableCountdown;
	bool _movingLeft, _movingRight;
	bool _suspendFriction;

	unsigned int _upgradeMask;

	std::shared_ptr<Shield> _shield;

};