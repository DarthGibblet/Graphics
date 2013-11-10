#include "Utils.h"

ResourceHolder::ResourceHolder(cleanup_func_t cleanupFunc) :
	_cleanupFunc(cleanupFunc)
{
}

ResourceHolder::~ResourceHolder()
{
	if(_cleanupFunc)
		_cleanupFunc();
}