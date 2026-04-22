#pragma once
#include "RiseEngineCore/Core/CoreCommon.hpp"
#include <vendor/OpenGL/GLEW/include/GL/glew.h>
#include <vector>

/*
* Call SetData<T>() after construction.
* 
* If you want to create a Index Buffer target should be GL_ELEMENT_ARRAY_BUFFER.
*/
class VBO
{
public:
	VBO();
	~VBO();
	
	/*
	* @brief Binds the VBO to the specified usage.
	* @param target Specifies the target to which the buffer object is bound. E.g. GL_ARRAY_BUFFER, GL_ELEMENT_ARRAY_BUFFER.
	*/
	void Bind(const uint32 target = GL_ARRAY_BUFFER) const;

	/*
	* @brief Unbind the VBO to the specified usage.
	* @param target Specifies the target to which the buffer object is bound. E.g. GL_ARRAY_BUFFER, GL_ELEMENT_ARRAY_BUFFER.
	*/
	void Unbind() const;
	
	/* @brief Binds the VBO to the specified usage.
	* @param target Specifies the target to which the buffer object is bound. E.g. GL_ARRAY_BUFFER, GL_ELEMENT_ARRAY_BUFFER.
	* @param verticesData The data to be stored in the VBO, for example the vertices data of a shape.
	* @param usage This is for example the mode GL_STATIC_DRAW for static objects.
	*/
	template<typename T>
	void SetData(const uint32 target, const std::vector<T>& verticesData, uint32 usage = GL_STATIC_DRAW)
	{
		Bind(target);
		glBufferData(target, verticesData.size() * sizeof(T), verticesData.data(), usage);
	}
private:
	uint32 id_;
	mutable uint32 target_; // Target this VBO is currently bound.
};

