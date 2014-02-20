#pragma once

#include "Utils.h"

#include <GL/glew.h>

#include <boost/format.hpp>

#include <string>
#include <memory>

class Shader
{
public:
	Shader(const std::string& filePathBase);
	Shader(const std::string& vertexFilePath, const std::string& fragFilePath);
	~Shader();

	void Activate();
	void Deactivate();

	float GetUniform(const std::string& varName);
	void SetUniform(const std::string& varName, const float& varVal);

	std::shared_ptr<ResourceHolder> ActivateScoped();

private:
	bool Init(const std::string& vertexFilePath, const std::string& fragFilePath, boost::format& errorMsg);

	GLuint _vertexShaderId, _fragShaderId, _shaderId;
};