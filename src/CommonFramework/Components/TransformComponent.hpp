#pragma once
#include "EntityComponent.hpp"
#include "CommonFramework/Transform.hpp"

namespace RiseEngine::CommonFramework
{
    class TransformComponent : public EntityComponent
    {
    public:
		explicit TransformComponent(const std::string& name = "SceneComponent");
		~TransformComponent() override = default;

		void AttachTo(TransformComponent* parent);
		void Detach();
		TransformComponent* GetParent() const { return parent_; }
		const std::vector<TransformComponent*>& GetChildren() const { return children_; }

		// World transform (absolute).
		glm::mat4 GetWorldMatrix() const;

		void SetLocalPosition(const glm::vec3& position);
		void SetLocalRotation(const glm::quat& rotation);
		void SetLocalScale(const glm::vec3& scale);
		void SetLocalTransform(const Transform& transform);

		// Local transform (relative to parent).
		const glm::vec3& GetLocalPosition() const { return localTransform_.position; }
		const glm::quat& GetLocalRotation() const { return localTransform_.rotation; }
		const glm::vec3& GetLocalScale() const { return localTransform_.scale; }
		Transform& GetLocalTransform() { return localTransform_; }
		const Transform& GetLocalTransform() const { return localTransform_; }

	private:
		Transform localTransform_;
		TransformComponent* parent_ = nullptr;
		std::vector<TransformComponent*> children_;
    };
}
