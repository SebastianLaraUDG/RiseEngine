#include <Rendering/include/VAO.hpp>
// #include <GL/glew.h>
#include <vendor/OpenGL/glad/include/glad/glad.h>

VAO::VAO()
{
	glGenVertexArrays(1, &id_);
}

VAO::~VAO()
{
	glDeleteVertexArrays(1, &id_);
}

void VAO::Bind() const
{
	glBindVertexArray(id_);
}

void VAO::Unbind() const
{
	glBindVertexArray(0);
}

void VAO::SetLayout(const int32 rowLength, const int32 index, const int32 size, const uint32 type, const uint8 normalized, const void* offset) const
{
	Bind();
	const int32 stride = static_cast<int32>(GetTypeSize(type) * rowLength); // cast is to prevent warnings in output and error list.
	glVertexAttribPointer(index, size, type, normalized, stride, offset);
	glEnableVertexAttribArray(index);
}

unsigned long long VAO::GetTypeSize(const uint32 type) const
{
	switch (type)
	{
	case GL_BYTE:				return sizeof(int8);		break;
	case GL_UNSIGNED_BYTE:		return sizeof(uint8);		break;
	case GL_SHORT:				return sizeof(int16);		break;
	case GL_UNSIGNED_SHORT:		return sizeof(uint16);		break;
	case GL_INT:				return sizeof(int32);		break;
	case GL_UNSIGNED_INT:		return sizeof(uint32);		break;
	case GL_FLOAT:				return sizeof(f32);			break;
	case GL_DOUBLE:				return sizeof(f64);			break;
	
	default:	return -1; // Invalid type.
		break;
	}
}
