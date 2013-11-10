#pragma once

#include <functional>

struct ResourceHolder
{
	typedef std::function<void()> cleanup_func_t;

	ResourceHolder(cleanup_func_t cleanupFunc);
	~ResourceHolder();
private:
	cleanup_func_t _cleanupFunc;

};