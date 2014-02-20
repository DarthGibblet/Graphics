#pragma once

#include "Box.h"
#include "Texture.h"
#include "Shader.h"

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
		enum E { Generic, Block, Player, Enemy, Bullet, Upgrade, Camera, Exit, END };
	};

	struct EnemyType
	{
		enum E { Generic, Tornado, END };
	};

	struct Core
	{
		Core();
		Core(const Object::Type::E& type, const glm::vec3& pos, const glm::vec3& size);

		bool StreamInsert(std::ofstream& stream) const;
		bool StreamExtract(std::ifstream& stream);

		Type::E _type;
		glm::vec3 _pos, _size, _vel;
	};

	Object();
	Object(const Object::Core& core);
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

	Object::Type::E Type() const;
	virtual Object::Type::E OwnerType() const;
	void Vel(const glm::vec3& vel);
	const glm::vec3& Vel() const;
	const glm::vec3& Pos() const;
	void Pos(const glm::vec3& pos);
	const glm::vec3& PrevPos() const;
	const glm::vec3& Size() const;
	void Size(const glm::vec3& size);
	void IsAlive(const bool isAlive);
	bool IsAlive();
	void Text(const std::string& textPath);

	bool StreamInsert(std::ofstream& stream) const;
	bool StreamExtract(std::ifstream& stream);
protected:
	Core _core;
	glm::vec3 _rotAxis, _vel;
	double _rotAngle;
	bool _falls;
	glm::vec3 _prevPos;

	bool _isAlive, _facingBackwards;
	
	static std::map<std::string, std::shared_ptr<Texture>> _textureCache;
	std::shared_ptr<Texture> _text;
	std::shared_ptr<Shader> _shader;
	Box _mesh;
	GLuint _glQueryId;
};