#include "Shader.h"

#include <iostream>
#include <fstream>

using std::cout;
using std::endl;

Shader::Shader(const std::string& filePathBase) : _vertexShaderId(0), _fragShaderId(0), _shaderId(0)
{
	boost::format initErrorMsg;
	if(!Init(filePathBase + ".vp", filePathBase + ".fp", initErrorMsg))
		cout <<initErrorMsg <<endl;
}

Shader::Shader(const std::string& vertexFilePath, const std::string& fragFilePath)
{
	boost::format initErrorMsg;
	if(!Init(vertexFilePath, fragFilePath, initErrorMsg))
		cout <<initErrorMsg <<endl;
}

Shader::~Shader()
{
	glDetachShader(_shaderId, _fragShaderId);
	glDetachShader(_shaderId, _vertexShaderId);

	glDeleteShader(_fragShaderId);
	glDeleteShader(_vertexShaderId);
	glDeleteShader(_shaderId);
}

bool Shader::Init(const std::string& vertexFilePath, const std::string& fragFilePath, boost::format& errorMsg)
{
	_shaderId = glCreateProgram();

	auto ReadAndCompileShader = [this, &errorMsg](const std::string& filePath, bool isVertexShader) -> bool
	{
		std::string shaderType = isVertexShader ? "vertex" : "fragment";
		auto& targetShaderId = isVertexShader ? _vertexShaderId : _fragShaderId;

		std::ifstream fin(filePath);

		if(!fin.is_open())
		{
			char errorDetail[128];
			strerror_s(errorDetail, errno);
			errorMsg = boost::format("Error attempting to open %s shader file \"%s\": %s") %
				shaderType % filePath % errorDetail;
			return false;
		}

		std::string text((std::istreambuf_iterator<char>(fin)), (std::istreambuf_iterator<char>()));
		auto textCStr = text.c_str();

		targetShaderId = glCreateShader(isVertexShader ? GL_VERTEX_SHADER : GL_FRAGMENT_SHADER);

		glShaderSource(targetShaderId, 1, &textCStr, 0);
		glCompileShader(targetShaderId);

		//Check the result to make sure the shader compiled
		GLint compileRes = GL_FALSE;
		glGetShaderiv(targetShaderId, GL_COMPILE_STATUS, &compileRes);
		if(compileRes != GL_TRUE)
		{
			char compileErrorLog[8192];
			GLsizei actualLogSize = 0;
			glGetShaderInfoLog(targetShaderId, 8192, &actualLogSize, compileErrorLog);
			errorMsg = boost::format("Error compiling %s shader \"%s\":\n%s") % shaderType % filePath % compileErrorLog;
			return false;
		}

		glAttachShader(_shaderId, targetShaderId);

		return true;
	};

	if(!ReadAndCompileShader(vertexFilePath, /*isVertexShader*/true))
		return false;
	if(!ReadAndCompileShader(fragFilePath, /*isVertexShader*/false))
		return false;

	glLinkProgram(_shaderId);

	return true;
}

void Shader::Activate()
{
	glUseProgram(_shaderId);
}

void Shader::Deactivate()
{
	glUseProgram(0);
}

std::shared_ptr<ResourceHolder> Shader::ActivateScoped()
{
	Activate();
	return std::make_shared<ResourceHolder>(std::bind(&Shader::Deactivate, this));
}