#include <Rendering/include/VAO.h>
#include <GL/glew.h>

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

void VAO::SetLayout(const int32 rowLength, const int32 index, const int32 size, const uint type, const uchar normalized, const void* offset) const
{
	const int32 stride = GetTypeSize(type) * rowLength;
	glVertexAttribPointer(index, size, type, normalized, stride, offset);
	glEnableVertexAttribArray(index);
}

unsigned long long VAO::GetTypeSize(const uint type) const
{
	switch (type)
	{
	case GL_BYTE:				return SIZE_IN_BYTES(signed char);		break;
	case GL_UNSIGNED_BYTE:		return SIZE_IN_BYTES(uchar);			break;
	case GL_SHORT:				return SIZE_IN_BYTES(short);			break;
	case GL_UNSIGNED_SHORT:		return SIZE_IN_BYTES(ushort);			break;
	case GL_INT:				return SIZE_IN_BYTES(int32);			break;
	case GL_UNSIGNED_INT:		return SIZE_IN_BYTES(uint32);			break;
	case GL_FLOAT:				return SIZE_IN_BYTES(float);			break;
	case GL_DOUBLE:				return SIZE_IN_BYTES(double);			break;
	
	default:	return -1; // Invalid type.
		break;
	}
}
