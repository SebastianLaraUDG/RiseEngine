#include "Rendering/include/Shader.h"
#include <fstream>
#include <sstream>
#include <RiseEngineCore/DebugIncludes/DebugIncludes.h>

Shader::Shader(const char* vertexPath, const char* fragmentPath)
{
	// 1. retrieve the vertex/fragment source code from filePath
	std::string vertexCode;
	std::string fragmentCode;
	std::ifstream vShaderFile;
	std::ifstream fShaderFile;
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
		std::cout << "ERROR::SHADER::FILE_NOT_SUCCESSFULLY_READ: " << e.what() << "\n";
	}
	const char* vShaderCode = vertexCode.c_str();
	const char* fShaderCode = fragmentCode.c_str();
	// 2. Compile shaders.
	// Vertex shader
	uint32 vertex = createShader(GL_VERTEX_SHADER, vShaderCode);
	glCheckError();
	/* TODO: delete this code. I'm just keeping it for reference and avoid conflicts.
	vertex = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex, 1, &vShaderCode, NULL);
	glCompileShader(vertex);
	checkCompileErrors(vertex, "VERTEX");
	*/
	// Fragment Shader.
	/*
	fragment = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment, 1, &fShaderCode, NULL);
	glCompileShader(fragment);
	checkCompileErrors(fragment, "FRAGMENT");
	*/
	uint32 fragment = createShader(GL_FRAGMENT_SHADER, fShaderCode);
	glCheckError();
	// shader Program
	rendererId_ = createProgram(vertex, fragment);
	glCheckError();
	/* TODO: deprecated.Remove.
	rendererId_ = glCreateProgram();
	glAttachShader(rendererId_, vertex);
	glAttachShader(rendererId_, fragment);
	glLinkProgram(rendererId_);
	checkCompileErrors(rendererId_, "PROGRAM");
	*/
	// delete the shaders as they're linked into our program now and no longer necessary
	glDeleteShader(vertex);
	glDeleteShader(fragment);
	use();
}

Shader::~Shader()
{
	glDeleteProgram(rendererId_);
}

void Shader::use() const
{
	glUseProgram(rendererId_);
}

void Shader::unbind() const
{
	glUseProgram(0);
}


void Shader::checkCompileErrors(uint shader, std::string type)
{
	int32 success;
	char infoLog[1024];
	if (type != "PROGRAM")
	{
		glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(shader, 1024, NULL, infoLog);
			std::cout << "ERROR::SHADER_COMPILATION_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- --\n";
		}
	}
	else
	{
		glGetProgramiv(shader, GL_LINK_STATUS, &success);
		if (!success)
		{
			glGetProgramInfoLog(shader, 1024, NULL, infoLog);
			std::cout << "ERROR::PROGRAM_LINKING_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- \n";
		}
	}
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


uint32 Shader::createShader(uint32 shaderType, const char* shaderCode)
{
	// Create the shader
	uint32 shaderProgram = glCreateShader(shaderType);
	glShaderSource(shaderProgram, 1, &shaderCode, NULL);
	glCompileShader(shaderProgram);

	// Log error if compilation failed and  abort.
	if (!CheckCompilationStatus(shaderProgram))
	{
		std::cout << "FAILED TO COMPILE SHADERS" << std::endl;
	}
	return shaderProgram;

	/*
	uint32 program = glCreateProgram();
	glAttachShader(program, vertexShader);
	glAttachShader(program, fragmentShader);
	glLinkProgram(program);
	

	// TODO: DEPRECATED
	uint32 shader = glCreateShader(shaderType);
	glShaderSource(shader, 1, &shaderCode, NULL);
	glCompileShader(shader);
	checkCompileErrors(shader, type);
	return shader;
	*/
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
