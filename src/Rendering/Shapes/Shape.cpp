#include "Shape.h"
#include <Rendering/include/Shader.h>

std::vector<float> Shape::VERTICES_DATA = {
	// XYZ				|| Vertex color (RGBA)
	-1.0f,+0.0f,+0.0f,	1.0f,0.0f,0.0f,1.0f,
	+0.0f,+1.0f,+0.0f,	0.0f,1.0f,0.0f,1.0f,
	+1.0f,+0.0f,+0.0f,	0.0f,0.0f,1.0f,1.0f
};

Shape::Shape()
{
	vao_.Bind();
	vbo_.Bind(GL_ARRAY_BUFFER);
	vbo_.SetData<float>(GL_ARRAY_BUFFER, VERTICES_DATA);
	vao_.SetLayout(7, 0, 3); // Position attribute.
	vao_.SetLayout(7, 1, 4, GL_FLOAT, GL_FALSE, (void*)(3 * SIZE_IN_BYTES(float))); // Color attribute.
}

void Shape::render() const
{
	vao_.Bind();
	// TODO: for now I will use the non-optimal drawing method.
	glDrawArrays(GL_TRIANGLES, 0, 3); // To draw multiple triangles that share vertices
									  // I should use glDrawElements();
	
	vao_.Unbind(); // TODO: This is here temporarily to get used to opengl workflow. Remove later.
}
