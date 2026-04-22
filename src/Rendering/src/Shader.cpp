#include "Rendering/include/Shader.hpp"
#include <Rendering/include/GLErrorLibrary.hpp>
#include <fstream>
#include <sstream>
#include <iostream>

Shader::Shader(const std::string& vertexPath, const std::string& fragmentPath) : rendererId_(0)
{
	LoadShader(vertexPath, fragmentPath);
}

Shader::~Shader()
{
	glDeleteProgram(rendererId_);
}

void Shader::LoadShader(const std::string& vertexPath, const std::string& fragmentPath)
{
	// If there was a loaded shader, delete it safely.
	if (rendererId_ != 0)
	{
		glDeleteProgram(rendererId_);
	}
	// 1. retrieve the vertex/fragment source code from filePath
	std::string vertexCode;
	std::string fragmentCode;
	std::ifstream vShaderFile;
	std::ifstream fShaderFile;

	/* MODERN LAMBDA. TODO: test
	auto readFile = [](const std::string& path) ->std::string
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
	vertexCode = readFile(vertexPath);
	fragmentCode = readFile(fragmentPath);
	*/

	// ensure ifstream objects can throw exceptions:
	vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	try
	{
		// open files
		vShaderFile.open(vertexPath);
		fShaderFile.open(fragmentPath);
		std::stringstream vShaderStream, fShaderStream;
		// read file's buffer contents into streams
		vShaderStream << vShaderFile.rdbuf();
		fShaderStream << fShaderFile.rdbuf();
		// close file handlers
		vShaderFile.close();
		fShaderFile.close();
		// convert stream into string
		vertexCode = vShaderStream.str();
		fragmentCode = fShaderStream.str();
	}
	catch (std::ifstream::failure& e)
	{
		std::cout << "ERROR::SHADER::FILE_READ_FAILED: " << e.what() << "\n";
	}
	const char* vShaderCode = vertexCode.c_str();
	const char* fShaderCode = fragmentCode.c_str();
	// 2. Compile shaders.
	// Vertex shader
	uint32 vertex = createShader(GL_VERTEX_SHADER, vShaderCode);
	glCheckError();

	// Fragment Shader.
	uint32 fragment = createShader(GL_FRAGMENT_SHADER, fShaderCode);
	glCheckError();
	// Shader Program.
	rendererId_ = createProgram(vertex, fragment);
	glCheckError();

	// Delete the shaders as they're linked into our program now and no longer necessary
	glDeleteShader(vertex);
	glDeleteShader(fragment);
	use();
}

Shader::~Shader()
{
	glDeleteProgram(rendererId_);
}

void Shader::Bind() const
{
	glUseProgram(rendererId_);
}

void Shader::Unbind() const
{
	glUseProgram(0);
}

int32 Shader::GetUniformLocation(const std::string& name) const
{
	// Location was previously cached.
	if (uniformLocationCache_.find(name) != uniformLocationCache_.end())
	{
		return uniformLocationCache_[name];
	}

	int32 location = glGetUniformLocation(rendererId_, name.c_str());
	if (location == -1)
	{
		std::cout << "ERROR: Uniform " << name << " does not exist\n";
	}
	uniformLocationCache_[name] = location;
	return location;
}

bool Shader::CheckStatus(uint32 program, PFNGLGETSHADERIVPROC getIVFunction, uint32 statusToCheck, PFNGLGETPROGRAMINFOLOGPROC getInfoLogFunc)
{
	int32 status;
	getIVFunction(program, statusToCheck, &status);

	if (status != GL_TRUE)
	{
		int32 infoLength;
		getIVFunction(program, GL_INFO_LOG_LENGTH, &infoLength);
		char* buffer = new char[infoLength];
		int32 bufferSize;

		getInfoLogFunc(program, infoLength, &bufferSize, buffer);

		// Log error.
		std::cout << " ERROR ON STATUS CHECK: " << buffer << std::endl;

		delete[] buffer;
		return false; // Failure.
	}
	// Success.
	return true;
}

bool Shader::CheckCompilationStatus(const uint32& shaderProgram)
{
	return CheckStatus(shaderProgram, glGetShaderiv, GL_COMPILE_STATUS, glGetShaderInfoLog);
}

bool Shader::CheckLinkingStatus(const uint32& program)
{
	return CheckStatus(program, glGetProgramiv, GL_LINK_STATUS, glGetProgramInfoLog);
}


uint32 Shader::createShader(uint32 shaderType, const std::string& shaderCode)
{
	// Create the shader
	uint32 shaderProgram = glCreateShader(shaderType);
	const char* src = shaderCode.c_str();
	glShaderSource(shaderProgram, 1, &src, NULL);
	glCompileShader(shaderProgram);

	// Log error if compilation failed and  abort.
	if (!CheckCompilationStatus(shaderProgram))
	{
		std::cout << "FAILED TO COMPILE SHADERS" << std::endl;
	}
	return shaderProgram;
}

uint32 Shader::createProgram(uint32 vertexShader, uint32 fragmentShader)
{
	uint32 program = glCreateProgram();
	glAttachShader(program, vertexShader);
	glAttachShader(program, fragmentShader);
	glLinkProgram(program);
	if (!CheckLinkingStatus(program))
	{
		std::cout << "FAILED TO LINK PROGRAM" << std::endl;
	}
	glValidateProgram(program);

	// Delete the shaders as they're linked into
	// our program now and no longer necessary.
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	return program;
}
