#pragma once
#include <CommonFramework/Components/EntityComponent.hpp>
#include <CommonFramework/Components/TransformComponent.hpp>
#include <unordered_set>

namespace RiseEngine
{
	class World;
}

namespace RiseEngine::CommonFramework
{
	// Base class for all entities in the world.
	// Always has a Root Component (TransformComponent)
	// that defines its position in the world.
	class Entity
	{
	public:
		explicit Entity(const std::string& name = "Entity");
		virtual ~Entity() = default;

		virtual void Update(f32 deltaTime);
		void Destroy();

		// Tags.
		inline void AddTag(const std::string& tag) { tags_.insert(tag); }
		inline void RemoveTag(const std::string& tag) { tags_.erase(tag); }
		inline bool HasTag(const std::string& tag) const { return tags_.contains(tag); }
		inline const std::unordered_set<std::string>& GetTags() const { return tags_; }

		// Components.
		template<typename T, typename... Args>
		T* AddComponent(Args&&... args)
		{
			static_assert(std::is_base_of_v<EntityComponent, T>, "T must be a subclass of EntityComponent");
			
			auto component = std::make_unique<T>(std::forward<Args>(args)...);
			T* ptr = component.get();
			ptr->SetOwner(this);
			ptr->OnAttach();
			components_.emplace_back(std::move(component));
			return ptr;
		}

		template<typename T>
		T* GetComponent() const
		{
			for (const auto& component : components_)
			{
				if (T* casted = dynamic_cast<T*>(component.get()))
				{
					return casted;
				}
			}
			return nullptr;
		}

		template<typename T>
		bool HasComponent() const
		{
			return GetComponent<T>() != nullptr;
		}

		void RemoveComponent(EntityComponent* component);

		// Getters.
		inline const std::string& GetName() const { return name_; }
		inline TransformComponent* GetRootComponent() const { return rootComponent_; }
		inline bool IsActive() const { return bActive_; }
		inline bool IsUpdatingComponents() const { return bUpdateComponentsEnabled_; }
		void SetActive(const bool active) { bActive_ = active; }

		inline World* GetWorld() const { return world_; }

	private:
		std::string name_;
		bool bActive_ = true;
		bool bUpdateComponentsEnabled_ = true;
		TransformComponent* rootComponent_ = nullptr;
		std::vector<std::unique_ptr<EntityComponent>> components_;
		std::unordered_set<std::string> tags_;

		friend class RiseEngine::World;
		World* world_ = nullptr;
		void SetWorld(World* world) { world_ = world; }
	};
}