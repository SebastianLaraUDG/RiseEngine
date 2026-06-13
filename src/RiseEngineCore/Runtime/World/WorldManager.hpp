#pragma once
#include <vector>
#include <memory>
#include <string>

namespace RiseEngine
{
	class World;

	/*
	* Manages the active world and world lifecycle.
	* Future features:
	* - Async world loading
	* - Sublevels within a world
	* - Multiple world contexts
	*/
	class WorldManager
	{
	public:
		WorldManager() = delete;

		static void Init();
		static void Shutdown();

		static World* CreateWorld(const std::string& name = "DefaultWorldName");
		static void DestroyWorld(World* world);
		static void SetActiveWorld(World* world);

		inline static World* GetActiveWorld() { return s_activeWorld_; }
		inline static bool HasActiveWorld() { return s_activeWorld_ != nullptr; }
		
	private:
		static World* s_activeWorld_;
		static std::vector<std::unique_ptr<World>> s_loadedWorlds_;
	};
}