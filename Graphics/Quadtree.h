#pragma once

#include "Object.h"

#include <vector>
#include <memory>
#include <functional>

class Quadtree
{
public:
	void Update(const double& secondsSinceLastUpdate);
	void Draw();
	void Insert(std::shared_ptr<Object> obj);

private:
	void RunFunctionOnAllTrackedObjects(std::function<void(std::shared_ptr<Object>)> func);

	std::vector<std::shared_ptr<Object>> _trackedObjs;
};