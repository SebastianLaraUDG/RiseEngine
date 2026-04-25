#include <Rendering/include/VBO.hpp>
#include <glad/glad.h>

VBO::VBO() : target_(0)
{
	glGenBuffers(1, &id_);
}

VBO::~VBO()
{
	glDeleteBuffers(1, &id_);
}

void VBO::Bind(const uint32 target) const
{
	target_ = target;
	glBindBuffer(target, id_);
}

void VBO::Unbind() const
{
	glBindBuffer(target_, 0);
}

void VBO::SetDataRaw(const uint32 target, const void* data, uint32 sizeBytes, uint32 usage)
{
	Bind(target);
	glBufferData(target, sizeBytes, data, usage);
}
