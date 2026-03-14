#include <Rendering/include/VBO.h>
#include <RiseEngineCore/ErrorHandling/ErrorHandler.h>

VBO::VBO()
{
	glGenBuffers(1, &id_);
}

VBO::~VBO()
{
	glDeleteBuffers(1, &id_);
}

void VBO::Bind(const uint target) const
{
	glBindBuffer(target, id_);
}

void VBO::Unbind(const uint target) const
{
	glBindBuffer(target, 0);
}