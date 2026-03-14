#pragma once
#include "RiseEngineCore/Core/CoreCommon.h"
#include <GL/glew.h>

class VAO
{
public:
	// Create a single object.
	VAO();
	~VAO();

	void Bind() const;
	void Unbind() const;
	
	/*
	* @brief Defines an array of generic vertex attribute data and specifies how OpenGL should interpret the vertex data in the currently bound VBO. This function is used to specify the layout of the vertex data in the VBO, for example how many floats are used for position, how many for color, etc.
	* @param rowLength The length of a row of data, for example if the vertices data has 3 floats for position and 4 floats for color, the row length would be 7.
	* @param index The index of the generic vertex attribute to be modified.
	* @param size Specifies the number of components per generic vertex attribute. Must be 1, 2, 3, 4. Additionally, the symbolic constant GL_BGRA is accepted
	* @param type The data type of each component in the array. Example: GL_BYTE, GL_UNSIGNED_BYTE, GL_FLOAT, GL_SHORT, GL_UNSIGNED_SHORT, GL_INT, and GL_UNSIGNED_INT.
	* @param normalized Whether fixed-point data values should be normalized (GL_TRUE) or converted directly as fixed-point values (GL_FALSE) when they are accessed.
	* @param offset Specifies a offset of the first component of the first generic vertex attribute in the array in the data store of the buffer currently bound to the GL_ARRAY_BUFFER target.
	*/
	void SetLayout(const int32 rowLength, const int32 index, const int32 size, const uint type = GL_FLOAT, const uchar normalized = GL_FALSE, const void* offset = (void*)0) const;

private:
	/* @brief Returns the size in bytes of the specified OpenGL data type. This is used to calculate the stride and offset when setting the vertex attribute pointers.
	*/
	unsigned long long GetTypeSize(const uint type) const;

	uint id_;
};