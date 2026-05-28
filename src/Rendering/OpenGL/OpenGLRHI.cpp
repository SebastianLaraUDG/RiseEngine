#include "OpenGLRHI.hpp"
#include <glad/glad.h>
#include <Rendering/OpenGL/OpenGLShader.hpp>
#include <Rendering/OpenGL/OpenGLVertexBuffer.hpp>
#include <Rendering/OpenGL/OpenGLVertexArray.hpp>

using OpenGLRHI = RiseEngine::Rendering::OpenGL::OpenGLRHI;
using namespace RiseEngine::Rendering;

void OpenGLRHI::Init()
{
	SetClearColor(0.f, 0.f, 0.f, 0.f);
	SetPolygonMode(RiseEngine::Rendering::EPolygonMode::Fill);
	glEnable(GL_DEPTH_TEST);
}

void OpenGLRHI::Shutdown()
{
}

void OpenGLRHI::SetClearColor(f32 r, f32 g, f32 b, f32 a)
{
	glClearColor(r, g, b, a);
}

void OpenGLRHI::Clear(EClearFlags flags) // TODO: I think this should be a smaller function. Keep this for now.
{
	uint32 glFlags = 0;
	if (HasFlag(flags, EClearFlags::Color))		glFlags |= GL_COLOR_BUFFER_BIT;
	if (HasFlag(flags, EClearFlags::Depth))		glFlags |= GL_DEPTH_BUFFER_BIT;
	if (HasFlag(flags, EClearFlags::Stencil))	glFlags |= GL_STENCIL_BUFFER_BIT;
	glClear(glFlags);
}

void OpenGLRHI::SetPolygonMode(EPolygonMode mode)
{
	uint32 polygonMode = (mode == EPolygonMode::Wireframe) ? GL_LINE : GL_FILL;
	glPolygonMode(GL_FRONT_AND_BACK, polygonMode);
}

void OpenGLRHI::DrawPrimitive(uint32 vertexCount, EPrimitiveType primitiveType, uint32 startVertex)
{
	glDrawArrays(TranslatePrimitive(primitiveType), startVertex, vertexCount);
}

void OpenGLRHI::DrawIndexed(uint32 indexCount, EPrimitiveType primitiveType, uint32 startIndex)
{
	glDrawElements(TranslatePrimitive(primitiveType), indexCount, GL_UNSIGNED_INT, (void*)(startIndex * sizeof(uint32)));
}

std::unique_ptr<IVertexBuffer> OpenGLRHI::CreateVertexBuffer(const void* data, uint32 size,
	EBufferFrequency frequency,	EBufferAccess access)
{
	return std::make_unique<OpenGLVertexBuffer>(data, size, frequency, access);
}

std::unique_ptr<IShader> OpenGLRHI::CreateShader(const std::string& vertPath, const std::string& fragPath)
{
	return std::make_unique<OpenGLShader>(vertPath, fragPath);
}

std::unique_ptr<IVertexArray> RiseEngine::Rendering::OpenGL::OpenGLRHI::CreateVertexArray()
{
	return std::unique_ptr<OpenGLVertexArray>();
}

uint32 OpenGLRHI::TranslatePrimitive(EPrimitiveType primitiveType)
{
	switch (primitiveType)
	{
	case EPrimitiveType::Triangles:		return GL_TRIANGLES;
	case EPrimitiveType::Lines:			return GL_LINES;
	case EPrimitiveType::Points:		return GL_POINTS;
	}
	return GL_TRIANGLES; // Safe fallback.
}
