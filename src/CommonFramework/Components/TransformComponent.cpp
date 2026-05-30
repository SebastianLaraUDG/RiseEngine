#include "pch.h"
#include "TransformComponent.hpp"

using TransformComponent = RiseEngine::CommonFramework::TransformComponent;

TransformComponent::TransformComponent(const std::string& name) : EntityComponent(name)
{}

void TransformComponent::AttachTo(TransformComponent* parent)
{
	// Detach from current parent if it exists.
	if (parent_)
	{
		Detach();
	}
	parent_ = parent;

	if (parent_)
	{
		parent_->children_.push_back(this);
	}
}

void TransformComponent::Detach()
{
	if (!parent_) return;

	std::vector<TransformComponent*>& siblings = parent_->children_;
	std::erase(siblings, this);
	parent_ = nullptr;
}

glm::mat4 TransformComponent::GetWorldMatrix() const
{
	if(parent_)
		return parent_->GetWorldMatrix() * localTransform_.GetMatrix();
	return localTransform_.GetMatrix();
}
