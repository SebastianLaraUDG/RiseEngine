#pragma once
#include "RiseEngineCore/Core/CoreCommon.h"
#include <string>
#include <vendor/OpenGL/GLEW/include/GL/glew.h>

class Shader
{
public:
	Shader(const char* vertexPath, const char* fragmentPath);
	~Shader();

	void use() const;
	void unbind() const;

	// TODO: uniform utility (bool, int, float mainly)

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
	static uint32 createShader(uint32 shaderType, const char* shaderCode);
	
	/// <summary>
	/// Creates a program ID.
	/// </summary>
	/// <param name="vertexShader"></param>
	/// <param name="fragmentShader"></param>
	/// <returns></returns>
	static uint32 createProgram(uint32 vertexShader, uint32 fragmentShader);

	uint rendererId_;
};