#include "Public/StaticMeshComponent.h"

StaticMeshComponent::StaticMeshComponent()
{
	Init(); // Initialize in the constructor to support later refactoring.
}

StaticMeshComponent::~StaticMeshComponent()
{
	DeInit();
}


void StaticMeshComponent::Init()
{
	/*
	* Replace: vertex data.
	* Shader path.
	*/

	/*
	* Currentyl generates a triangle with 2 attributes for the vertex:
	* Location and color.
	*/
	// Triangle data. CAN BE REPLACED WITH DIFFERENT SHAPES.
	const float VERTICES_DATA[] =
	{
		// XYZ				|| Vertex color (RGBA)
		-1.0f,+0.0f,+0.0f,	1.0f,0.0f,0.0f,1.0f,
		+0.0f,+1.0f,+0.0f,	0.0f,1.0f,0.0f,1.0f,
		+1.0f,+0.0f,+0.0f,	0.0f,0.0f,1.0f,1.0f
	};
	
	constexpr int32 DATA_ROW_LENGTH = 7; // 3 For position + 4 for color.

	shader = std::make_unique<Shader>(
		"../Rendering/Assets/Shaders/Basic2DTriangle/VertexShader.glsl",
		"../Rendering/Assets/Shaders/Basic2DTriangle/FragmentShader.glsl");
	
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	// Binding
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, SIZE_IN_BYTES(VERTICES_DATA), VERTICES_DATA, GL_STATIC_DRAW);


	// Position attribute
	constexpr int32 stride = SIZE_IN_BYTES(float) * DATA_ROW_LENGTH;
	glVertexAttribPointer(0, DIMENSION_3, GL_FLOAT, GL_FALSE, stride, (void*)0);
	glEnableVertexAttribArray(0);
	// Color attribute
	glVertexAttribPointer(1, RGBA_DIMENSION, GL_FLOAT, GL_FALSE, stride, (void*)(DIMENSION_3 * SIZE_IN_BYTES(float)));
	glEnableVertexAttribArray(1);
}

void StaticMeshComponent::DeInit()
{
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
}