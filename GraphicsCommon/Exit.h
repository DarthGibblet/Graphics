#pragma once

#include "Object.h"

#include <string>
#include <functional>

class Exit : public Object
{
public:
	typedef std::function<void(const std::string&, const uint32_t&)> env_change_func_t;
	Exit(const Object::Core& core, const std::string& newEnvName, const uint32_t& newEnvEntranceId, const env_change_func_t& envChangeFunc);

	virtual void Draw() override;
	virtual void HandleCollision(Object* other) override;
	virtual bool UsePreciseCollisions() override;

protected:
	std::string _newEnvName;
	uint32_t _newEnvEntranceId;
	env_change_func_t _envChange;

};