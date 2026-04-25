#pragma once
#include "RiseEngineCore/Core/CoreCommon.hpp"
// #include <vendor/OpenGL/GLEW/include/GL/glew.h>
#include <vendor/OpenGL/glad/include/glad/glad.h>
#include <unordered_map>
#include <string>

class Shader
{
public:
	Shader(const std::string& vertexPath, const std::string& fragmentPath);
	~Shader();

	void LoadShader(const std::string& vertexPath, const std::string& fragmentPath);
	void Bind() const;
	void Unbind() const;

	int32 GetUniformLocation(const std::string& name) const;
	
	template <typename T>
	void SetUniform(const std::string& name, T v0);

	template <typename T>
	void SetUniform(const std::string& name, T v0, T v1);

	template <typename T>
	void SetUniform(const std::string& name, T v0, T v1, T v2);

	template <typename T>
	void SetUniform(const std::string& name, T v0, T v1, T v2, T v3);
	
private:
		
	/// <summary>
	/// Check status of provided program and functions (e.g. a shader and compilation status or a program and linking status).
	/// </summary>
	/// <param name="program">Shader, Program, etc.</param>
	/// <param name="getIVFunction">glGetShaderiv, glGetProgramiv, etc.</param>
	/// <param name="statusToCheck">GL_COMPILE_STATUS, GL_LINK_STATUS, etc.</param>
	/// <param name="getInfoLogFunc">glGetShaderInfoLog, glGetProgramInfoLog, etc.</param>
	/// <returns></returns>
	static bool CheckStatus(uint32 program, PFNGLGETSHADERIVPROC getIVFunction,uint32 statusToCheck, PFNGLGETPROGRAMINFOLOGPROC getInfoLogFunc);
	
	/// <summary>
	/// Check compilation status of a shader. Logs error if compilation failed.
	/// </summary>
	/// <param name="shaderProgram">A shader program to check compilation status.</param>
	/// <returns>True if compiled successfully. False otherwise.</returns>
	static bool CheckCompilationStatus(const uint32& shaderProgram);

	/// <summary>
	/// Check linking status of a program. Logs error if linking failed.
	/// </summary>
	/// <param name="program">Program to check linking status.</param>
	/// <returns>True if linking succeeded, false otherwise.</returns>
	static bool CheckLinkingStatus(const uint32& program);

	/// <summary>
	/// Create a shader program, which already checked for compilation erros.
	/// </summary>
	/// <param name="shaderType">GL_VERTEX_SHADER, FRAGMENT_SHADER, etc.</param>
	/// <param name="type">VERTEX, FRAGMENT, or PROGRAM.</param>
	/// <param name="shaderCode">Shader source code. Read from a different GLSL file.</param>
	/// <returns>A shader program which already checked for compilation errors.</returns>
	
	/// <summary>
	/// Create a single shader (it does not create a vertex and fragment shader at the same time).
	/// </summary>
	/// <param name="shaderType">Vertex/Fragment.</param>
	/// <param name="shaderCode">The GLSL source code of the shader.(Note this is not a file path).</param>
	/// <returns>A SHADER program (ID).</returns>
	static uint32 createShader(uint32 shaderType, const std::string& shaderCode);
	
	/// <summary>
	/// Creates a program ID.
	/// </summary>
	/// <param name="vertexShader"></param>
	/// <param name="fragmentShader"></param>
	/// <returns></returns>
	static uint32 createProgram(uint32 vertexShader, uint32 fragmentShader);

private:

	uint32 rendererId_;
	mutable std::unordered_map<std::string, int32> uniformLocationCache_;
};

// Generals.
template<typename T>
inline void Shader::SetUniform(const std::string& name, T v0)
{
	//
}
template<typename T>
inline void Shader::SetUniform(const std::string& name, T v0, T v1)
{
	//
}
template<typename T>
inline void Shader::SetUniform(const std::string& name, T v0, T v1, T v2)
{
	//
}
template<typename T>
inline void Shader::SetUniform(const std::string& name, T v0, T v1, T v2, T v3)
{
	//
}

/* Integer specializations. */
template <>
inline void Shader::SetUniform<int32>(const std::string& name, int32 v0)
{
	glUniform1i(GetUniformLocation(name.c_str()), v0);
}

template <>
inline void Shader::SetUniform<int32>(const std::string& name, int32 v0, int32 v1)
{
	glUniform2i(GetUniformLocation(name.c_str()), v0, v1);
}

template <>
inline void Shader::SetUniform<int32>(const std::string& name, int32 v0, int32 v1, int32 v2)
{
	glUniform3i(GetUniformLocation(name.c_str()), v0, v1, v2);
}

template <>
inline void Shader::SetUniform<int32>(const std::string& name, int32 v0, int32 v1, int32 v2, int32 v3)
{
	glUniform4i(GetUniformLocation(name.c_str()), v0, v1, v2, v3);
}

/* Float specializations. */

template <>
inline void Shader::SetUniform<f32>(const std::string& name, f32 v0)
{
	glUniform1f(GetUniformLocation(name.c_str()), v0);
}

template <>
inline void Shader::SetUniform<f32>(const std::string& name, f32 v0, f32 v1)
{
	glUniform2f(GetUniformLocation(name.c_str()), v0, v1);
}

template <>
inline void Shader::SetUniform<f32>(const std::string& name, f32 v0, f32 v1, f32 v2)
{
	glUniform3f(GetUniformLocation(name.c_str()), v0, v1, v2);
}

template <>
inline void Shader::SetUniform<f32>(const std::string& name, f32 v0, f32 v1, f32 v2, f32 v3)
{
	glUniform4f(GetUniformLocation(name.c_str()), v0, v1, v2, v3);
}