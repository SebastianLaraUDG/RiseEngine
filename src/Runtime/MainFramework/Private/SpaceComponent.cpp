#include "Public/SpaceComponent.h"

void SpaceComponent::Update(float deltaTime)
{
	//
}

void SpaceComponent::SetLocation(const Vector3& InLocation)
{
	transform_.location = InLocation;
}

void SpaceComponent::SetRotation(const Vector3& InRotation)
{
	transform_.rotation = InRotation;
}