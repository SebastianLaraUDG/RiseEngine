#pragma once
#include <RiseEngineCore/Core/CoreCommon.hpp>
#include "GLFlags.hpp"

class VAO;
class IBO; // TODO: Implement class.
class Shader;


class Renderer
{
public:
	// Black background.
	Renderer();
	// Custom background color
	explicit Renderer(f32 r, f32 g, f32 b, f32 a);
	~Renderer();
	void Draw(const VAO& vao, const IBO& ibo, const Shader& shader) const;
	void Draw(const VAO& vao, const class VBO& vbo, const Shader& shader) const;
	void Clear(RiseEngine::Rendering::ClearFlags clearFlags = RiseEngine::Rendering::DefaultClearFlags) const;
	
	/*
	* @brief Enable or disable a rendering capacity.
	* @param capacity - The capacity to enable/disable, for example GL_DEPTH_TEST or GL_LIGHTING.
	* @param bNewEnabled - True to enable the supplied capacity, false to disable.
	 */
	void SetCapacityEnabled(uint32 capacity, bool bNewEnabled);


	/*
	* @param mode - GL_FILL for normal rendering or GL_LINE for wireframe mode.
	* @param face -
	*/
	void SetRenderingMode(uint32 mode = GL_FILL, uint32 face = GL_FRONT_AND_BACK);

	// Wrapper because I am going to switch from glew to glad and I dont know if it is gonna be different.
	// TODO: remove if unnecessary.
	void SetClearColor(f32 r, f32 g, f32 b, f32 a);
private:
};