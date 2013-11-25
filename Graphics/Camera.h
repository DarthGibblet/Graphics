#pragma once

#include "Object.h"

#include <GL/glew.h>

class Camera : public Object
{
public:
	Camera(const double& maxX, const double& ratio);
	virtual void Update(const double& secondsSinceLastFrame) override;
	virtual void Draw() override;
	virtual void Teather(Object* followedObj);
	//virtual void Restrict(const double& maxXPos, const double maxYPos);

	void SetRestrictLeft(const double& restrictLeft);
	void SetRestrictRight(const double& restrictRight);
	void SetRestrictTop(const double& restrictTop);
	void SetRestrictBottom(const double& restrictBottom);
protected:
	Object* _followedObj;
	double _maxX, _maxY;
	double _restrictLeft, _restrictRight, _restrictTop, _restrictBottom;
};