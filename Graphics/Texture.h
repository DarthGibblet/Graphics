#pragma once

#include "DataFile.h"

#include "Utils.h"

#include <GL/glew.h>

#include <boost/format.hpp>

#include <string>
#include <fstream>
#include <memory>

class Texture : public DataFile
{
public:
	Texture(const std::string& filePath);

	void Activate(int targetTextureUnit	 = 0);
	void Deactivate(int targetTextureUnit = 0);

	std::shared_ptr<ResourceHolder> ActivateScoped(int targetTextureUnit = 0);

private:
	bool HandleDataRead(const std::string& fileCode, std::ifstream& fin, boost::format& errorMsg) override;

	static void Set(GLuint textureId, int targetTextureUnit);

	GLuint _textureId;
};