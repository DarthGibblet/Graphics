#pragma once

#include "Box.h"
#include "Texture.h"

#include <glm/glm.hpp>

#include <string>
#include <map>
#include <vector>
#include <memory>

class Object
{
public:
	struct Type
	{
		enum E { Generic, Block, Player, Enemy, Bullet, Upgrade, Camera };
	};

	Object(const glm::vec3& pos, const glm::vec3& size, const std::string& textPath, bool falls, Type::E type);
	
	virtual ~Object();

	virtual void Update(const double& secondsSinceLastUpdate, /*out*/std::vector<std::shared_ptr<Object>>& objList);
	virtual void Draw();

	bool DoesCollide(std::shared_ptr<Object> other);
	bool DoesCollide(Object* other);
	void HandleCollision(std::shared_ptr<Object> other);
	virtual void HandleCollision(Object* other);
	bool IsContainedByBox(const glm::vec3& boxCenter, const double& boxWidth, const double& boxHeight);
	bool UsePreciseCollisions();

	Type::E Type() const;
	virtual Type::E OwnerType() const;
	void Vel(const glm::vec3& vel);
	const glm::vec3& Vel() const;
	const glm::vec3& Pos() const;
	const glm::vec3& PrevPos() const;
	const glm::vec3& Size() const;
	void IsAlive(const bool isAlive);
	bool IsAlive();
	void Text(const std::string& textPath);
protected:
	glm::vec3 _pos, _size, _rotAxis, _vel;
	double _rotAngle;
	bool _falls;
	glm::vec3 _prevPos;
	Type::E _type;

	bool _isAlive, _facingBackwards;
	
	static std::map<std::string, std::shared_ptr<Texture>> _textureCache;
	std::shared_ptr<Texture> _text;
	Box _mesh;
	GLuint _glQueryId;
};