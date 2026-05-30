#include "CameraComponent.hpp"
#include <vendor/glm/glm.hpp>

using CameraComponent = RiseEngine::CommonFramework::CameraComponent;


CameraComponent::CameraComponent(const f32 FOVDegrees, const f32 aspectRatio, const f32 near, const f32 far, const std::string& name) : TransformComponent(name)
{
	SetPerspective(FOVDegrees, aspectRatio, near, far);
}

CameraComponent::CameraComponent(const f32 left, const f32 right, const f32 top, const f32 bottom, const f32 near, const f32 far, const std::string& name) : TransformComponent(name)
{
	SetOrthographic(left, right, bottom, top, near, far);
}

void CameraComponent::SetPerspective(const f32 fovDegrees, const f32 aspectRatio, const f32 nearClip, const f32 farClip)
{
	projectionType_ = ECameraProjectionType::Perspective;
	fov_ = fovDegrees;
	aspectRatio_ = aspectRatio;
	nearClip_ = nearClip;
	farClip_ = farClip;
	projection_ = glm::perspective(glm::radians(fovDegrees), aspectRatio, nearClip, farClip);
}

void CameraComponent::SetOrthographic(const f32 left, const f32 right, const f32 bottom, const f32 top, const f32 nearClip, const f32 farClip)
{
	projectionType_ = ECameraProjectionType::Orthographic;
	nearClip_ = nearClip;
	farClip_ = farClip;
	projection_ = glm::ortho(left, right, bottom, top, nearClip, farClip);
}

void CameraComponent::SetAspectRatio(const f32 aspectRatio)
{
	if (projectionType_ == ECameraProjectionType::Perspective)
	{
		SetPerspective(fov_, aspectRatio, nearClip_, farClip_);
	}
}

glm::mat4 CameraComponent::GetViewMatrix() const
{
	// Extract position and orientation from the world matrix.
	// Always right-handed (-Z forward) — the RHI will adapt to the active API.
	glm::mat4 worldMatrix = GetWorldMatrix();
	glm::vec3 position = glm::vec3(worldMatrix[3]);
	glm::vec3 forward = -glm::vec3(worldMatrix[2]); // -Z forward (right-handed)
	glm::vec3 up = glm::vec3(worldMatrix[1]);

	return glm::lookAt(position, position + forward, up);
}
