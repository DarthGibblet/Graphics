#pragma once

#include "Object.h"

#include <vector>
#include <functional>

class Quadtree
{
public:
	Quadtree(const glm::vec3& pos, const double& width, const double& height, int depth = 0);
	~Quadtree();
	void Update(const double& secondsSinceLastUpdate);
	void Draw();
	void Insert(Object* obj);

private:
	void CheckCollisions();
	void CheckCollisionsWithObject(Object* obj);

	std::vector<Object*> _trackedObjs;

	glm::vec3 _pos;
	double _width, _height;
	int _depth;
	std::vector<Quadtree*> _children;

	const static int MAX_DEPTH = 4;
	const static int MAX_OBJ_COUNT = 25;
	static float _gridColors[MAX_DEPTH + 1][3];
};