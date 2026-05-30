#pragma once
#include "TransformComponent.hpp"

namespace RiseEngine::CommonFramework
{
	enum class ECameraProjectionType : uint8
	{
		Perspective,
		Orthographic
	};

    class CameraComponent : public TransformComponent
    {
    public:
		// Build perspective projection with the given FOV, aspect ratio, near, and far planes.
		CameraComponent(const f32 FOVDegrees, const f32 aspectRatio, const f32 near, const f32 far, const std::string& name = "CameraComponent");
		// Build orthographic projection with the given left, right, top, bottom, near, and far planes.
		CameraComponent(const f32 left, const f32 right, const f32 top, const f32 bottom, const f32 near, const f32 far, const std::string& name = "CameraComponent");
		~CameraComponent() override = default;

		// Projection.

		void SetPerspective(const f32 fovDegrees, const f32 aspectRatio, const f32 nearClip, const f32 farClip);
		void SetOrthographic(const f32 left, const f32 right, const f32 bottom, const f32 top, const f32 nearClip, const f32 farClip);
		void SetAspectRatio(const f32 aspectRatio);
		
	public:
		// Getters.

		// Matrices — right-handed, depth range -1 to 1
		// The RHI adapts these to the active API's conventions
		inline const glm::mat4& GetProjectionMatrix() const { return projection_; }
		glm::mat4 GetViewMatrix() const;
		inline glm::mat4 GetViewProjection() const { return projection_ * GetViewMatrix(); }
		
		inline ECameraProjectionType GetProjectionType() const { return projectionType_; }
		inline f32 GetFOV() const { return fov_; }
		inline f32 GetNearClip() const { return nearClip_; }
		inline f32 GetFarClip() const { return farClip_; }

	private:
		glm::mat4 projection_;
		ECameraProjectionType projectionType_;

		f32 fov_ = 45.f;
		f32 aspectRatio_ = 1.f;
		f32 nearClip_ = 0.1f;
		f32 farClip_ = 1000.f;
    };
}