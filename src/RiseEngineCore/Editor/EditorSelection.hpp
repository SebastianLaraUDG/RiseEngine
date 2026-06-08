#pragma once

namespace RiseEngine::CommonFramework
{
	class Entity;
}

namespace RiseEngine::Editor
{
	// Shared state between editor panels.
	// The Outliner writes to it, the Details panel reads from it.
	class EditorSelection
	{
		using Entity = RiseEngine::CommonFramework::Entity;
	public:
		void Select(Entity* entity) { selectedEntity_ = entity; }
		void Deselect() { selectedEntity_ = nullptr; }

		Entity* GetSelectedEntity() const { return selectedEntity_; }
		bool HasSelection() const { return selectedEntity_ != nullptr; }
	private:
		Entity* selectedEntity_ = nullptr;
	};
}