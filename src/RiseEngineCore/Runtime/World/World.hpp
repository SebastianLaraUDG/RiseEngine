#pragma once
#include <string>
#include <memory>

namespace RiseEngine
{
	namespace CommonFramework
	{
		class Entity;
	}

	/*
	* You can think of the world also as the level.
	*/
	class World final
	{
		using Entity = CommonFramework::Entity;
	public:
		explicit World(const std::string& name);
		~World() = default;

		// TODO: initialize world from file data.

		void Update(const f32 deltaTime);

		Entity* CreateEntity(const std::string& entityName = "Entity");
		void DestroyEntity(Entity* entity);
	private:
		std::string name_;
		std::vector<std::unique_ptr<Entity>> entities_; // All the entities in this world.
	};
}