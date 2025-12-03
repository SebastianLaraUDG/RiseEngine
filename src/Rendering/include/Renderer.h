#pragma once
#include <GL/glew.h>

class Renderer
{
public:
	Renderer() = default;
	~Renderer() {}

	const char* getString() const { return "Sebas"; }

private:
	unsigned int id;
};