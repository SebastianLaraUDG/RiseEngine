#include <Rendering/include/Renderer.hpp>
#include <Rendering/include/GLErrorLibrary.hpp>
#include <Rendering/include/Shader.hpp>
#include <Rendering/include/VAO.hpp>
#include <Rendering/include/VBO.hpp>
#include <glad/glad.h>

Renderer::Renderer()
{
	SetClearColor(0.0f, 0.0f, 0.0f, 1.0f);
}

Renderer::Renderer(f32 r, f32 g, f32 b, f32 a)
{
	SetClearColor(r, g, b, a);
}

Renderer::~Renderer()
{
	//
}

void Renderer::Draw(const VAO& vao, const IBO& ibo, const Shader& shader) const
{
	shader.Bind();
	vao.Bind();
	// ibo.bind();
	// 
	// glDrawArrays
	// glDrawElements
}

void Renderer::Draw(const VAO& vao, const VBO& vbo, const Shader& shader) const
{
	shader.Bind();
	vao.Bind();
	vbo.Bind(GL_ARRAY_BUFFER);
	glDrawArrays(GL_TRIANGLES, 0, 3); // Simple triangle, temporal.
	glCheckError();
}

void Renderer::Clear(uint32 mask) const
{
	glClear(mask);
}

void Renderer::SetCapacityEnabled(uint32 capacity, bool bNewEnabled)
{
	bNewEnabled ? glEnable(capacity) : glDisable(capacity);
}


void Renderer::SetRenderingMode(uint32 mode, uint32 face)
{
	glPolygonMode(face, mode);
}

void Renderer::SetClearColor(f32 r, f32 g, f32 b, f32 a)
{
	glClearColor(r, g, b, a);
}