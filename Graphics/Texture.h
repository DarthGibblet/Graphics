#pragma once

#include "Utils.h"

#include <GL/glew.h>

#include <string>
#include <memory>

class Texture
{
public:
	Texture(const std::string& filePath);

	void Activate(int targetTextureUnit	 = 0);
	void Deactivate(int targetTextureUnit = 0);

	std::shared_ptr<ResourceHolder> ActivateScoped(int targetTextureUnit = 0);

private:

	static void Set(GLuint textureId, int targetTextureUnit);

	GLuint _textureId;
};