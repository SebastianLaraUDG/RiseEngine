#include "OpenGLShader.hpp"
#include <glad/glad.h>
#include <Rendering/include/GLErrorLibrary.hpp>
#include <vendor/glm/gtc/type_ptr.hpp>
#include <fstream>
#include <iostream>

using OpenGLShader = RiseEngine::Rendering::OpenGLShader;

OpenGLShader::OpenGLShader(const std::string& vertexPath, const std::string& fragmentPath)
	: id_(0)
{
	std::string vertexSource;
	std::string fragmentSource;

	auto readFile = [](const std::string& path) -> std::string
		{
			std::ifstream file(path, std::ios::in);
			if (!file.is_open())
			{
				throw std::runtime_error("Cannot open file: " + path + ". Message from: " + __FILE__);
			}
			return std::string(
				std::istreambuf_iterator<char>(file),
				std::istreambuf_iterator<char>()
			);
		};

	vertexSource = readFile(vertexPath);
	fragmentSource = readFile(fragmentPath);

	uint32 vert = CompileShader(GL_VERTEX_SHADER, vertexSource);
	glCheckError();
	uint32 frag = CompileShader(GL_FRAGMENT_SHADER, vertexSource);
	glCheckError();

	id_ = LinkProgram(vert, frag);
	glCheckError();

	// Ya linkeados, los shaders individuales no se necesitan más
	glDeleteShader(vert);
	glDeleteShader(frag);
}

OpenGLShader::~OpenGLShader()
{
	glDeleteProgram(id_);
}

void OpenGLShader::Bind() const
{
	glUseProgram(id_);
}

void OpenGLShader::Unbind() const
{
	glUseProgram(0);
}

void RiseEngine::Rendering::OpenGLShader::SetInt(const std::string& name, int32 value)
{
	glUniform1i(GetUniformLocation(name), value);
}

void RiseEngine::Rendering::OpenGLShader::SetFloat(const std::string& name, f32 value)
{
	glUniform1f(GetUniformLocation(name), value);
}

void RiseEngine::Rendering::OpenGLShader::SetDouble(const std::string& name, f64 value)
{
	glUniform1d(GetUniformLocation(name), value);
}

void RiseEngine::Rendering::OpenGLShader::SetVec3(const std::string& name, const glm::vec3& value)
{
	glUniform3fv(GetUniformLocation(name), 1, glm::value_ptr(value));
}

void RiseEngine::Rendering::OpenGLShader::SetVec4(const std::string& name, const glm::vec4& value)
{
	glUniform4fv(GetUniformLocation(name), 1, glm::value_ptr(value));
}

void RiseEngine::Rendering::OpenGLShader::SetMat4(const std::string& name, const glm::mat4& value)
{
	glUniformMatrix4fv(GetUniformLocation(name), 1, GL_FALSE, glm::value_ptr(value));
}

int32 OpenGLShader::GetUniformLocation(const std::string& name) const
{
	if (uniformLocationCache_.find(name) != uniformLocationCache_.end())
	{
		return uniformLocationCache_[name];
	}

	int32 location = glGetUniformLocation(id_, name.c_str());
	if (location == -1)
	{
		std::cout << "ERROR: Uniform " << name << " does not exist\n";
	}
	uniformLocationCache_[name] = location;
	return location;
}

uint32 OpenGLShader::CompileShader(uint32 shaderType, const std::string& source)
{
	uint32 shaderProgram = glCreateShader(shaderType);
	const char* src = source.c_str();
	glShaderSource(shaderProgram, 1, &src, NULL);
	glCompileShader(shaderProgram);

	// Log error if compilation failed and  abort.
	if (!CheckStatus(shaderProgram, glGetShaderiv, GL_COMPILE_STATUS, glGetShaderInfoLog))
	{
		std::cout << "FAILED TO COMPILE SHADERS" << std::endl;
	}
	return shaderProgram;
}

uint32 OpenGLShader::LinkProgram(uint32 vertexShader, uint32 fragmentShader)
{
	uint32 program = glCreateProgram();
	glAttachShader(program, vertexShader);
	glAttachShader(program, fragmentShader);
	glLinkProgram(program);

	if (!CheckStatus(program, glGetProgramiv, GL_LINK_STATUS, glGetProgramInfoLog))
	{
		std::cout << "FAILED TO LINK PROGRAM\n";
	}
	glValidateProgram(program);
	return program;
}

bool OpenGLShader::CheckStatus(uint32 object, std::function<void(uint32, uint32, int32*)> getIV, uint32 statusToCheck, std::function<void(uint32, int32, int32*, char*)> getInfoLog)
{
	int32 status;
	getIV(object, statusToCheck, &status);
	if (status == GL_TRUE) return true;

	int32 logLength;
	getIV(object, GL_INFO_LOG_LENGTH, &logLength);
	char* buffer = new char[logLength + 1];
	int32 written;
	getInfoLog(object, logLength, &written, buffer);
	std::cout << "Shader ERROR: " << buffer << "\n";
	delete buffer;
	return false;
}
