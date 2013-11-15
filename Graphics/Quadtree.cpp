#include "Quadtree.h"

#include <algorithm>

void Quadtree::Update(const double& secondsSinceLastUpdate)
{
	RunFunctionOnAllTrackedObjects(std::bind(&Object::Update, std::placeholders::_1, secondsSinceLastUpdate));
}

void Quadtree::Draw()
{
	RunFunctionOnAllTrackedObjects(std::bind(&Object::Draw, std::placeholders::_1));
}

void Quadtree::Insert(std::shared_ptr<Object> obj)
{
	_trackedObjs.push_back(obj);
}

void Quadtree::RunFunctionOnAllTrackedObjects(std::function<void(std::shared_ptr<Object>)> func)
{
	std::for_each(std::begin(_trackedObjs), std::end(_trackedObjs), func);
}