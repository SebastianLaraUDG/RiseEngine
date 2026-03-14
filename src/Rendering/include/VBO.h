#pragma once
#include "RiseEngineCore/Core/CoreCommon.h"
#include <GL/glew.h>
#include <vector>

class VBO
{
public:
	VBO();
	~VBO();
	
	/*
	* @brief Binds the VBO to the specified usage.
	* @param target Specifies the target to which the buffer object is bound. E.g. GL_ARRAY_BUFFER, GL_ELEMENT_ARRAY_BUFFER.
	*/
	void Bind(const uint target) const;

	/*
	* @brief Unbind the VBO to the specified usage.
	* @param target Specifies the target to which the buffer object is bound. E.g. GL_ARRAY_BUFFER, GL_ELEMENT_ARRAY_BUFFER.
	*/
	void Unbind(const uint target) const;
	
	/* @brief Binds the VBO to the specified usage.
	* @param target Specifies the target to which the buffer object is bound. E.g. GL_ARRAY_BUFFER, GL_ELEMENT_ARRAY_BUFFER.
	* @param verticesData The data to be stored in the VBO, for example the vertices data of a shape.
	* @param usage This is for example the mode GL_STATIC_DRAW for static objects.
	*/
	template<typename T>
	void SetData(const uint target, const std::vector<T>& verticesData, uint usage = GL_STATIC_DRAW) const
	{
		Bind(target);
		glBufferData(target, verticesData.size() * SIZE_IN_BYTES(T), verticesData.data(), usage);
	}
private:
	uint id_;
};

