#include "Quadtree.h"

#include <algorithm>

float Quadtree::_gridColors[MAX_DEPTH + 1][3] = {
	{ 1.0, 0.0, 0.0},
	{ 1.0, 0.5, 0.0},
	{ 1.0, 1.0, 0.0},
	{ 0.5, 1.0, 0.0},
	{ 0.0, 1.0, 0.0}
};

Quadtree::Quadtree(const glm::vec3& pos, const double& width, const double& height, int depth) : _pos(pos), _width(width), _height(height), _depth(depth)
{
	_trackedObjs.reserve(MAX_OBJ_COUNT);
}

Quadtree::~Quadtree()
{
	std::for_each(std::begin(_children), std::end(_children), [](decltype(*std::begin(_children)) child)
	{
		delete child;
	});
}

void Quadtree::Update(const double& secondsSinceLastUpdate)
{
	foreach(_trackedObjs, std::bind(&Object::Update, std::placeholders::_1, secondsSinceLastUpdate));
	foreach(_children, std::bind(&Quadtree::Update, std::placeholders::_1, secondsSinceLastUpdate));
	CheckCollisions();
}

void Quadtree::Draw(bool drawGraph)
{
	foreach(_children, std::bind(&Quadtree::Draw, std::placeholders::_1, drawGraph));
	foreach(_trackedObjs, std::bind(&Object::Draw, std::placeholders::_1));

	if(drawGraph)
	{
		glLineWidth(2.5);
		float currentColor[4];
		glGetFloatv(GL_CURRENT_COLOR, currentColor);
		glColor3f(_gridColors[_depth][0], _gridColors[_depth][1], _gridColors[_depth][2]);
		glPushMatrix();
		glTranslatef(_pos.x, _pos.y, _pos.z);

		glBegin(GL_LINE_LOOP);
		glVertex3f((float)-_width / 2, (float) _height / 2, 0);
		glVertex3f((float) _width / 2, (float) _height / 2, 0);
		glVertex3f((float) _width / 2, (float)-_height / 2, 0);
		glVertex3f((float)-_width / 2, (float)-_height / 2, 0);
		glEnd();
		glColor3f(currentColor[0], currentColor[1], currentColor[2]);

		glPopMatrix();
	}
}

void Quadtree::Insert(Object* obj)
{
	auto FindAppropriateChild = [this](Object* obj)
	{
		bool fitInChild = false;
		std::for_each(std::begin(_children), std::end(_children), [&fitInChild, &obj](decltype(*std::begin(_children)) child)
		{
			if(obj->IsContainedByBox(child->_pos, child->_width, child->_height))
			{
				child->Insert(obj);
				fitInChild = true;
			}
		});

		if(!fitInChild)
			_trackedObjs.push_back(obj);
	};

	if(_depth >= MAX_DEPTH || (_children.empty() && _trackedObjs.size() < MAX_OBJ_COUNT))
	{
		_trackedObjs.push_back(obj);
	}
	else if(_children.empty())
	{
		_children.push_back(new Quadtree(glm::vec3(_pos.x - _width / 4, _pos.y - _height / 4, 0), _width / 2, _height / 2, _depth + 1));
		_children.push_back(new Quadtree(glm::vec3(_pos.x + _width / 4, _pos.y - _height / 4, 0), _width / 2, _height / 2, _depth + 1));
		_children.push_back(new Quadtree(glm::vec3(_pos.x + _width / 4, _pos.y + _height / 4, 0), _width / 2, _height / 2, _depth + 1));
		_children.push_back(new Quadtree(glm::vec3(_pos.x - _width / 4, _pos.y + _height / 4, 0), _width / 2, _height / 2, _depth + 1));

		std::vector<Object*> tmpObjList;
		_trackedObjs.swap(tmpObjList);

		std::for_each(std::begin(tmpObjList), std::end(tmpObjList), FindAppropriateChild);
		FindAppropriateChild(obj);
	}
	else
	{
		FindAppropriateChild(obj);
	}
}

void Quadtree::CheckCollisions()
{
	for(auto iObj = std::begin(_trackedObjs); iObj < std::end(_trackedObjs); ++iObj)
	{
		for(auto jObj = iObj + 1; jObj < std::end(_trackedObjs); ++jObj)
		{
			if((*iObj)->DoesCollide(*jObj))
			{
				(*iObj)->HandleCollision(*jObj);
				(*jObj)->HandleCollision(*iObj);
			}
		}
	}

	auto endTrackedObjs = _trackedObjs.size();
	auto endChildren = _children.size();

	std::for_each(std::begin(_trackedObjs), std::end(_trackedObjs), [this](Object* obj)
	{
		foreach(_children, std::bind(&Quadtree::CheckCollisionsWithObject, std::placeholders::_1, obj));
	});
}

void Quadtree::CheckCollisionsWithObject(Object* higherObj)
{
	std::for_each(std::begin(_trackedObjs), std::end(_trackedObjs), [&higherObj](Object* localObj)
	{
		if(higherObj->DoesCollide(localObj))
		{
			higherObj->HandleCollision(localObj);
			localObj->HandleCollision(higherObj);
		}
	});

	foreach(_children, std::bind(&Quadtree::CheckCollisionsWithObject, std::placeholders::_1, higherObj));
}
