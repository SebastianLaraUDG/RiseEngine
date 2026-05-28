#include "OpenGLVertexArray.hpp"
#include <Rendering/include/Primitives/IVertexBuffer.hpp>
#include <glad/glad.h>

using OpenGLVertexArray = RiseEngine::Rendering::OpenGLVertexArray;

OpenGLVertexArray::OpenGLVertexArray()
{
	glGenVertexArrays(1, &id_);
}

OpenGLVertexArray::~OpenGLVertexArray()
{
	glDeleteVertexArrays(1, &id_);
}

void OpenGLVertexArray::Bind() const
{
	glBindVertexArray(id_);
}

void OpenGLVertexArray::Unbind() const
{
	glBindVertexArray(0);
}

void OpenGLVertexArray::SetLayout(const VertexLayout& layout, const IVertexBuffer& vbo)
{
	Bind();
	vbo.Bind();

	for (const VertexAttribute& attr : layout.attributes)
	{
		glEnableVertexAttribArray(attr.index);
		glVertexAttribPointer(attr.index,
			attr.componentCount,
			TranslateDataType(attr.dataType),
			attr.normalized ? GL_TRUE : GL_FALSE,
			layout.stride,
			(const void*)attr.offset); // reinterpret_cast<const void*>(static_cast<uintptr_t>(attr.offset))
										// read about this, TODO: test if this works better.

	}
}

uint32 OpenGLVertexArray::TranslateDataType(EVertexDataType type)
{
	switch (type)
	{
	case EVertexDataType::Float:        return GL_FLOAT;
	case EVertexDataType::Int:          return GL_INT;
	case EVertexDataType::UnsignedInt:  return GL_UNSIGNED_INT;
	case EVertexDataType::Byte:         return GL_BYTE;
	case EVertexDataType::UnsignedByte: return GL_UNSIGNED_BYTE;
	}
	return GL_FLOAT; // Safe fallback.
					 // Set gl_float since it is the most common among all the options.
}
