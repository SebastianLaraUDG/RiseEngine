#include "World.hpp"
#include <CommonFramework/WorldObjects/Entity.hpp>
#include <algorithm>

using World = RiseEngine::World;
using Entity = RiseEngine::CommonFramework::Entity;

World::World(const std::string& name)
	:name_(name)
{
}

void World::Update(const f32 deltaTime)
{
	for (auto& entity : entities_)
	{
		if (entity->IsActive())
			entity->Update(deltaTime);
	}
}

Entity* World::CreateEntity(const std::string& entityName)
{
	auto entity = std::make_unique<Entity>(entityName);
	entity->SetWorld(this);
	Entity* ptr = entity.get();
	entities_.emplace_back(std::move(entity));
	return ptr;
}

void World::DestroyEntity(Entity* entity)
{
	std::erase_if(entities_, [entity](const std::unique_ptr<Entity>& e)
		{
			return e.get() == entity;
		}
	);
}