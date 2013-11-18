#pragma once

#include "Box.h"
#include "Texture.h"

#include <glm/glm.hpp>

#include <string>

class Object
{
public:
	Object(const glm::vec3& pos, const glm::vec3& size, const std::string& texPath, bool falls);

	void Update(const double& secondsSinceLastUpdate);
	void Draw();

	bool DoesCollide(std::shared_ptr<Object> other);
	bool DoesCollide(Object* other);
	void HandleCollision(std::shared_ptr<Object> other);
	void HandleCollision(Object* other);
	bool IsContainedByBox(const glm::vec3& boxCenter, const double& boxWidth, const double& boxHeight);
protected:
	glm::vec3 _pos, _size, _rotAxis, _vel;
	double _rotAngle;
	bool _falls;
	glm::vec3 _prevPos;
	
	Texture _tex;
	Box _mesh;
};