#include "OpenGLVertexBuffer.hpp"
#include <glad/glad.h>

using OpenGLVertexBuffer = RiseEngine::Rendering::OpenGL::OpenGLVertexBuffer;

OpenGLVertexBuffer::OpenGLVertexBuffer(const void* data, uint32 size,
	EBufferFrequency frequency, EBufferAccess access) : frequency_(frequency), access_(access)
{
	glGenBuffers(1, &id_);
	SetData(data, size);
}

OpenGLVertexBuffer::~OpenGLVertexBuffer()
{
	glDeleteBuffers(1, &id_);
}

void OpenGLVertexBuffer::Bind() const
{
	glBindBuffer(GL_ARRAY_BUFFER, id_);
}

void OpenGLVertexBuffer::Unbind() const
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void OpenGLVertexBuffer::SetData(const void* data, uint32 size)
{
	Bind();
	glBufferData(GL_ARRAY_BUFFER, size, data, Translate(frequency_, access_));
}

uint32 OpenGLVertexBuffer::Translate(EBufferFrequency frequency, EBufferAccess access)
{
    if (frequency == EBufferFrequency::Static)
    {
        if (access == EBufferAccess::Draw) return GL_STATIC_DRAW;
        if (access == EBufferAccess::Read) return GL_STATIC_READ;
        if (access == EBufferAccess::Copy) return GL_STATIC_COPY;
    }
    if (frequency == EBufferFrequency::Dynamic)
    {
        if (access == EBufferAccess::Draw) return GL_DYNAMIC_DRAW;
        if (access == EBufferAccess::Read) return GL_DYNAMIC_READ;
        if (access == EBufferAccess::Copy) return GL_DYNAMIC_COPY;
    }
    if (frequency == EBufferFrequency::Stream)
    {
        if (access == EBufferAccess::Draw) return GL_STREAM_DRAW;
        if (access == EBufferAccess::Read) return GL_STREAM_READ;
        if (access == EBufferAccess::Copy) return GL_STREAM_COPY;
    }

    return GL_STATIC_DRAW; // Safe fallback.
}