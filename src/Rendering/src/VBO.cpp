#include <Rendering/include/VBO.hpp>


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