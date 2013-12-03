#pragma once

#include "Box.h"
#include "Texture.h"

#include <glm/glm.hpp>

#include <string>

class Object
{
public:
	struct Type
	{
		enum E { Generic, Block, Player, Enemy, Bullet, Upgrade, Camera };
	};

	Object(const glm::vec3& pos, const glm::vec3& size, const std::string& texPath, bool falls, Type::E type);
	
	virtual ~Object();

	virtual void Update(const double& secondsSinceLastUpdate);
	virtual void Draw();

	bool DoesCollide(std::shared_ptr<Object> other);
	bool DoesCollide(Object* other);
	void HandleCollision(std::shared_ptr<Object> other);
	virtual void HandleCollision(Object* other);
	bool IsContainedByBox(const glm::vec3& boxCenter, const double& boxWidth, const double& boxHeight);
	bool UsePreciseCollisions();

	Type::E Type();
	void Vel(const glm::vec3& vel);
	const glm::vec3& Vel();
	const glm::vec3& Pos();
	const glm::vec3& PrevPos();
	const glm::vec3& Size();
	bool IsAlive();
protected:
	glm::vec3 _pos, _size, _rotAxis, _vel;
	double _rotAngle;
	bool _falls;
	glm::vec3 _prevPos;
	Type::E _type;

	bool _isAlive, _facingBackwards;
	
	Texture _tex;
	Box _mesh;
	GLuint _glQueryId;
};