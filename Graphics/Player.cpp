#include "Player.h"
#include "Constants.h"

Player::Player(const glm::vec3& pos, const unsigned int upgradeMask) : Entity(pos, glm::vec3(0.8, 1, 1), "..\\resources\\Gust.dds", true, Object::Type::Player),
		_jumpsRemaining(0), _isJumping(false), _wallJumpable(false), _dashTimer(0), _crouching(false), _dashReady(false), _dashing(false), _pendingCrouchRelease(false), 
		_movingLeft(false), _movingRight(false), _suspendFriction(true), _upgradeMask(upgradeMask)
{
}

void Player::Update(const double& secondsSinceLastUpdate, /*out*/std::vector<std::shared_ptr<Object>>& objList)
{
	_suspendFriction = false;

	if(_dashing)
	{
		_dashTimer += secondsSinceLastUpdate;
		if(_dashTimer >= 0.5)
		{
			_dashing = false;
			_dashTimer = 0;
			auto newVel = Vel();
			if(Vel().x < -MAX_PLAYER_WALKING_SPEED)
				newVel.x = static_cast<float>(-MAX_PLAYER_WALKING_SPEED);
			else if(Vel().x > MAX_PLAYER_WALKING_SPEED)
				newVel.x = static_cast<float>(MAX_PLAYER_WALKING_SPEED);
			Vel(newVel);
			_shield->IsAlive(false);
			_shield.reset();
		}
		_suspendFriction = true;
	}
	else
	{
		if(_pendingCrouchRelease && ((_standingClearanceZone && !_standingClearanceZone->IsColliding(Object::Type::Block)) || !_standingClearanceZone))
		{
			_crouching = false;
			_core._pos.y += _core._size.y/2;
			_core._size.y = _core._size.y * 2;
			auto newVel = Vel();
			if(Vel().x < -MAX_PLAYER_WALKING_SPEED)
				newVel.x = static_cast<float>(-MAX_PLAYER_WALKING_SPEED);
			else if(Vel().x > MAX_PLAYER_WALKING_SPEED)
				newVel.x = static_cast<float>(MAX_PLAYER_WALKING_SPEED);
			Vel(newVel);
			_pendingCrouchRelease = false;

			if(_standingClearanceZone)
			{
				_standingClearanceZone->IsAlive(false);
				_standingClearanceZone.reset();
			}
		}

		if(_movingLeft != _movingRight)
		{
			if(!_crouching)
			{
				if(_movingLeft && Vel().x > -MAX_PLAYER_WALKING_SPEED)
					Vel(Vel() + glm::vec3(-15 * secondsSinceLastUpdate, 0, 0));
				if(_movingRight && Vel().x < MAX_PLAYER_WALKING_SPEED)
					Vel(Vel() + glm::vec3(15 * secondsSinceLastUpdate, 0, 0));
			}
			else if(_dashReady)
			{
				if(_movingLeft)
					Vel(glm::vec3(-10, 0, 0));
				if(_movingRight)
					Vel(glm::vec3(10, 0, 0));
				_dashReady = false;
				_dashTimer = 0;
				_dashing = true;
				_shield = std::make_shared<Shield>(this);
				objList.push_back(_shield);

				if(_standingClearanceZone)
					_standingClearanceZone->IsAlive(false);
				_standingClearanceZone = std::make_shared<Zone>();
				objList.push_back(_standingClearanceZone);
			}

			_suspendFriction = true;
		}

		if(_wallJumpable)
		{
			auto lastWallJumpCountdown = _wallJumpableCountdown;
			_wallJumpableCountdown -= secondsSinceLastUpdate;
			if(_wallJumpableCountdown <= 0)
				_wallJumpable = false;
		}

		if(_isJumping && _jumpHoldTimer < MAX_JUMP_HOLD_DURATION)
		{
			auto tmpJumpVel = _curJumpVel;
			if(_curJumpVel.x == 0)
			{
				tmpJumpVel.x = Vel().x;
			}
			Vel(tmpJumpVel);
			_jumpHoldTimer += secondsSinceLastUpdate;
		}
	}

	_movingLeft = _movingRight = false;

	if(_standingClearanceZone)
	{
		auto pos = Pos();
		auto size = Size();
		pos.y += size.y;
		_standingClearanceZone->Pos(pos);
		_standingClearanceZone->Size(size);
		_standingClearanceZone->Reset();
	}

	Entity::Update(secondsSinceLastUpdate, objList);
}

void Player::HandleCollision(Object* other)
{
	Entity::HandleCollision(other);

	switch(other->Type())
	{
	case Object::Type::Block:
		if(_doesXCollide && !_doesXCollideLastFrame)
		{
			if(_upgradeMask & Upgrade::Type::WALL_JUMP)
				_wallJumpable = true;
			_wallJumpableCountdown = 0.5;
			_wallJumpLeft = Pos().x < other->Pos().x;
		}
		if(_doesYCollide && !_doesYCollideLastFrame)
		{
			if(!_suspendFriction)
				_vel.x = 0;
			if(Pos().y > other->Pos().y)
			{
				_jumpsRemaining = _upgradeMask & Upgrade::Type::DOUBLE_JUMP ? 2 : 1;
				_dashReady = true;
			}
		}
		break;
	case Object::Type::Upgrade:
		_upgradeMask |= reinterpret_cast<Upgrade*>(other)->Power();
		break;
	}
}

void Player::JumpHold()
{
	if(_wallJumpable)
	{
		_jumpHoldTimer = 0;
		_isJumping = true;
		_curJumpVel = glm::vec3((_wallJumpLeft ? -5 : 5), 2, 0);
	}
	else if(_jumpsRemaining > 0)
	{
		_jumpHoldTimer = 0;
		--_jumpsRemaining;
		_curJumpVel = glm::vec3(0, BASE_JUMP_STRENGTH, 0);
		_isJumping = true;
	}
}

void Player::JumpRelease()
{
	_jumpHoldTimer = 0;
	_isJumping = false;
}

void Player::CrouchHold()
{
	if(!_crouching )
	{
		_crouching = true;
		_core._pos.y -= _core._size.y / 4;
		_core._size.y = _core._size.y / 2;
		_pendingCrouchRelease = false;
	}
}

void Player::CrouchRelease()
{
	_pendingCrouchRelease = true;
}

void Player::MoveLeft()
{
	_movingLeft = true;
}

void Player::MoveRight()
{
	_movingRight = true;
}

std::shared_ptr<Bullet> Player::Fire()
{
	glm::vec3 bulletVel(_facingBackwards ? -BULLET_SPEED : BULLET_SPEED, 0, 0);
	return std::make_shared<Bullet>(Pos(), bulletVel, "..\\resources\\Bullet.dds", this);
}

unsigned Player::GetUpgradeMask() const
{
	return _upgradeMask;
}

bool Player::HasUpgrade(const Upgrade::Type::E& upgrade) const
{
	return (_upgradeMask & upgrade) != 0;
}
