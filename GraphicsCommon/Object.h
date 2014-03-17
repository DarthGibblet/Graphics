#pragma once

#include "Box.h"
#include "Texture.h"
#include "Shader.h"

#include <glm/glm.hpp>

#include <boost/static_assert.hpp>

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

		static std::string ToString(const unsigned int& val)
		{
			if(val < Type::END)
				return ToString(static_cast<Type::E>(val));
			return "";
		}

		static std::string ToString(const E& val)
		{
			BOOST_STATIC_ASSERT(Type::END == 8);
			static std::string convMap[Type::END];
			static bool initialized = false;
			if(!initialized)
			{
				convMap[Generic] = "Generic";
				convMap[Block] = "Block";
				convMap[Player] = "Player";
				convMap[Enemy] = "Enemy";
				convMap[Bullet] = "Bullet";
				convMap[Upgrade] = "Upgrade";
				convMap[Camera] = "Camera";
				convMap[Exit] = "Exit";
				initialized = true;
			}
			return convMap[val];
		}
	};

	struct EnemyType
	{
		enum E { Generic, Tornado, Boss, END };

		static std::string ToString(const unsigned int& val)
		{
			if(val < EnemyType::END)
				return ToString(static_cast<EnemyType::E>(val));
			return "";
		}
		static std::string ToString(const E& val)
		{
			BOOST_STATIC_ASSERT(EnemyType::END == 3);
			static std::string convMap[EnemyType::END];
			static bool initialized = false;
			if(!initialized)
			{
				convMap[Generic] = "Generic";
				convMap[Tornado] = "Tornado";
				convMap[Boss] = "Boss";
				initialized = true;
			}
			return convMap[val];
		}
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
	virtual bool UsePreciseCollisions();

	Object::Type::E Type() const;
	virtual Object::Type::E OwnerType() const;
	void Vel(const glm::vec3& vel);
	const glm::vec3& Vel() const;
	const glm::vec3& Pos() const;
	void Pos(const glm::vec3& pos);
	const glm::vec3& PrevPos() const;
	const glm::vec3& Size() const;
	void Size(const glm::vec3& size);
	virtual void IsAlive(const bool isAlive);
	virtual bool IsAlive() const;
	void FacingBackwards(const bool facingBackwards);
	bool FacingBackwards();
	void Text(const std::string& textPath);

	void SetDeathTimer(const double& secondsUtilDeath);

	bool StreamInsert(std::ofstream& stream) const;
	bool StreamExtract(std::ifstream& stream);
protected:
	Core _core;
	glm::vec3 _rotAxis, _vel;
	double _rotAngle;
	bool _falls;
	glm::vec3 _prevPos;

	bool _isAlive, _facingBackwards;
	double _deathTimer; //The number of seconds until this object dies. -1 indicates it is not set
	
	static std::map<std::string, std::shared_ptr<Texture>> _textureCache;
	std::shared_ptr<Texture> _text;
	std::shared_ptr<Shader> _shader;
	Box _mesh;
	GLuint _glQueryId;
};