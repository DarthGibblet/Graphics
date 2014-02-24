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

template<typename CONTAINER_T, typename FUNCTION_T>
inline void foreach(const CONTAINER_T& container, FUNCTION_T& func)
{
	//For some reason using std::for_each causes a drastic performance hit. Stick with the raw loop
	//std::for_each(std::begin(container), std::end(container), func);

	auto end = container.size();
	for(int i=0; i<end; ++i)
		func(container[i]);
}