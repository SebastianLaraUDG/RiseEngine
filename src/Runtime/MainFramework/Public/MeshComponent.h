#pragma once
#include "PrimitiveComponent.h"
#include "vendor/OpenGL/GLEW/include/GL/glew.h"
#include "Rendering/include/Shader.h"

/**
* @brief Abstract rendering.
The MeshComponent is responsible for storing the mesh data of the entity, which includes its vertices, indices and materials.
*/
class MeshComponent : public PrimitiveComponent
{
public:
	MeshComponent() = default;
	~MeshComponent();
protected:
	std::unique_ptr<Shader> shader;
	uint VAO, VBO;
};

