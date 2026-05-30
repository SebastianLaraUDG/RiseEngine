#pragma once
#include <RiseEngineCore/Core/CoreTypes.hpp>
#include <string>
#include <unordered_set>

namespace RiseEngine::CommonFramework
{
	class Entity;

	// Base class for all components that can be attached to an entity.
	class EntityComponent
	{
		explicit EntityComponent(const std::string& name);
		virtual ~EntityComponent() = default;
		virtual void OnAttach() {}
		virtual void OnDetach() {}
		virtual void Update(f32 deltaTime) {}

		inline void AddTag(const std::string& tag) { tags_.insert(tag); }
		inline void RemoveTag(const std::string& tag) { tags_.erase(tag); }
		inline bool HasTag(const std::string& tag) const { return tags_.contains(tag); }
		inline const std::unordered_set<std::string>& GetTags() const { return tags_; }

		const std::string& GetName() const { return name_; }
		bool IsActive() const { return bActive_; }
		void SetActive(const bool active) { bActive_ = active; }

		Entity* GetOwner() const { return owner_; }

	private:
		friend class Entity;
		void SetOwner(Entity* owner) { owner_ = owner; }
	private:
		std::string name_;
		std::unordered_set<std::string> tags_;
		bool bActive_ = true;
		Entity* owner_ = nullptr;
	};
}