#pragma once
#include <RiseEngineCore/Core.h>
#include <string>

class Shader
{
public:
	Shader(const char* vertexPath, const char* fragmentPath);
	~Shader() {}

	void use();

	// TODO: uniform utility (bool, int, float mainly)

private:
	void checkCompileErrors(uint shader, std::string type);

	uint id_;
};