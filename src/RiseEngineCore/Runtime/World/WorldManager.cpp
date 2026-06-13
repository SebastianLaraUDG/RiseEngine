#include "WorldManager.hpp"
#include "World.hpp"

using WorldManager = RiseEngine::WorldManager;
using World = RiseEngine::World;

World* WorldManager::s_activeWorld_ = nullptr;
std::vector<std::unique_ptr<World>> WorldManager::s_loadedWorlds_;

// Create default world on startup.
void WorldManager::Init()
{
	s_activeWorld_ = CreateWorld();
}

void WorldManager::Shutdown()
{
	s_activeWorld_ = nullptr;
	s_loadedWorlds_.clear();
}

World* WorldManager::CreateWorld(const std::string& name)
{
	std::unique_ptr<World> world = std::make_unique<World>(name);
	World* ptr = world.get();
	s_loadedWorlds_.emplace_back(std::move(world));
	return ptr;
}

void WorldManager::DestroyWorld(World* world)
{
	if (world == s_activeWorld_)
		s_activeWorld_ = nullptr;

	std::erase_if(s_loadedWorlds_, [world](const std::unique_ptr<World>& w)
		{
			return w.get();
		});
}

void WorldManager::SetActiveWorld(World* world)
{
	s_activeWorld_ = world;
}

