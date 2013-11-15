#pragma once

#include "Box.h"
#include "Texture.h"

#include <glm/glm.hpp>

#include <string>

class Object
{
public:
	Object(const glm::vec3& pos, const glm::vec3& size, const std::string& texPath);

	void Update(const double& secondsSinceLastUpdate);
	void Draw();
protected:
	glm::vec3 _pos, _size, _rotAxis;
	double _rotAngle;
	
	Texture _tex;
	Box _mesh;
};