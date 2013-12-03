#include "Player.h"
#include "Upgrade.h"

Player::Player(const glm::vec3& pos) : Object(pos, glm::vec3(0.8, 1, 1), "..\\resources\\Gust.dds", true, Object::Type::Player),
		_jumpsRemaining(0), _wallJumpable(false), _movingLeft(false), _movingRight(false), 
		_suspendFriction(true), _upgradeMask(0)
{
}

void Player::Update(const double& secondsSinceLastUpdate)
{
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

	_jumpHoldTimer += secondsSinceLastUpdate;

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
	_suspendFriction = false;
}

void Player::JumpHold()
{
	_jumpHoldTimer = 1;
	if(_jumpsRemaining <= 0 && _wallJumpable)
	{
		auto jumpVec = glm::vec3((_wallJumpLeft ? -10 : 10), 4, 0);
		Vel(Vel() + jumpVec);
	}
}

void Player::JumpRelease()
{
	glm::vec3 jumpVec;
	if(_jumpsRemaining > 0)
	{
		--_jumpsRemaining;
		jumpVec = glm::vec3(0, 3.5, 0);

		if(_jumpHoldTimer > 2)
			_jumpHoldTimer = 2;

		jumpVec *= _jumpHoldTimer;
		Vel(Vel() + jumpVec);
	}
}

void Player::MoveLeft()
{
	_movingLeft = true;
}

void Player::MoveRight()
{
	_movingRight = true;
}