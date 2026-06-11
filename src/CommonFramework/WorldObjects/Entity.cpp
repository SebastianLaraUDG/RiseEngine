#include "Entity.hpp"
#include <CommonFramework/Components/TransformComponent.hpp>
#include <RiseEngineCore/Runtime/World/World.hpp>

using Entity = RiseEngine::CommonFramework::Entity;

Entity::Entity(const std::string& name) : name_(name)
{
	rootComponent_ = AddComponent<TransformComponent>("RootComponent");
}

void Entity::Update(f32 deltaTime)
{
	if (!bActive_ || !bUpdateComponentsEnabled_) return;
	// Update all components.
	for (const auto& component : components_)
	{
		if (component->IsActive())
		component->Update(deltaTime);
	}
}

void Entity::Destroy()
{
	if (world_)
	{
		world_->DestroyEntity(this);
	}
}

void Entity::RemoveComponent(EntityComponent* component)
{
	if (component == rootComponent_) return;

	component->OnDetach();
	std::erase_if(components_, [component](const std::unique_ptr<EntityComponent>& ec)
		{
			return ec.get() == component;
		});
}