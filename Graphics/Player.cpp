#include "Player.h"
#include "Upgrade.h"
#include "Constants.h"

Player::Player(const glm::vec3& pos) : Object(pos, glm::vec3(0.8, 1, 1), "..\\resources\\Gust.dds", true, Object::Type::Player),
		_jumpsRemaining(0), _isJumping(false), _wallJumpable(false), _movingLeft(false), _movingRight(false), 
		_suspendFriction(true), _upgradeMask(0)
{
}

void Player::Update(const double& secondsSinceLastUpdate)
{
	_suspendFriction = false;
	if(_movingLeft != _movingRight)
	{
		if(_movingLeft && _vel.x > -5)
			Vel(Vel() + glm::vec3(-15 * secondsSinceLastUpdate, 0, 0));
		if(_movingRight && _vel.x < 5)
			Vel(Vel() + glm::vec3(15 * secondsSinceLastUpdate, 0, 0));

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

	_movingLeft = _movingRight = false;

	Object::Update(secondsSinceLastUpdate);
}

void Player::HandleCollision(Object* other)
{
	switch(other->Type())
	{
	case Type::Block:
		{
			//If we're colliding with a block, then there should be a dimension in which _prevPos wasn't colliding.
			//  Find which dimension that is, then reset _pos to match _prevPos along that axis.
			auto doesXCollide = abs(_pos.x - other->Pos().x) < _size.x / 2 + other->Size().x / 2;
			auto doesYCollide = abs(_pos.y - other->Pos().y) < _size.y / 2 + other->Size().y / 2;
			auto doesXCollideLastFrame = abs(_prevPos.x - other->PrevPos().x) < _size.x / 2 + other->Size().x / 2;
			auto doesYCollideLastFrame = abs(_prevPos.y - other->PrevPos().y) < _size.y / 2 + other->Size().y / 2;

			if(doesXCollide && !doesXCollideLastFrame)
			{
				_pos.x = _prevPos.x;
				_pos.y = _prevPos.y;
				_vel.y = 0;
				_vel.x = 0;
				if(_upgradeMask & Upgrade::Type::WALL_JUMP)
					_wallJumpable = true;
				_wallJumpableCountdown = 0.5;
				_wallJumpLeft = _pos.x < other->Pos().x;
			}
			if(doesYCollide && !doesYCollideLastFrame)
			{
				_pos.y = _prevPos.y;
				if(!_suspendFriction)
					_vel.x = 0;
				_vel.y = 0;
				if(Pos().y > other->Pos().y)
					_jumpsRemaining = _upgradeMask & Upgrade::Type::DOUBLE_JUMP ? 2 : 1;
			}
		}
		break;
	case Type::Bullet:
		break;
	case Type::Enemy:
		//_isAlive = false;
		break;
	case Type::Upgrade:
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
	return std::make_shared<Bullet>(_pos, bulletVel, "..\\resources\\Bullet.dds", this);
}