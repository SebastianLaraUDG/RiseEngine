#include "OpenGLIndexBuffer.hpp"
#include <glad/glad.h>

using OpenGLIndexBuffer = RiseEngine::Rendering::OpenGLIndexBuffer;

OpenGLIndexBuffer::OpenGLIndexBuffer(const uint32* indices, uint32 count, EBufferFrequency frequency, EBufferAccess access) : count_(count), frequency_(frequency), access_(access)
{
	glGenBuffers(1, &id_);
	Bind();
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(uint32), indices, Translate(frequency, access));
}

OpenGLIndexBuffer::~OpenGLIndexBuffer()
{
	glDeleteBuffers(1, &id_);
}

void OpenGLIndexBuffer::Bind() const
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, id_);
}

void OpenGLIndexBuffer::Unbind() const
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

uint32 OpenGLIndexBuffer::Translate(EBufferFrequency frequency, EBufferAccess access)
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
