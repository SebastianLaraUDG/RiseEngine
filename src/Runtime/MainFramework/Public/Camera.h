#pragma once
#include "Entity.h"
#include <filesystem>
#include <RiseEngineCore/Core/CoreCommon.h>
/*
* A first person camera.
*/
class Camera final : public Entity
{
public:
	Camera(const std::filesystem::path& jsonPath);
	~Camera() = default;

private:
	void ProcessKeyboardInput();
	void ProcessMouseInput();

	float movementSpeed_ = 1.f;
	float rotationSpeed_ = 1.f;
	Vector3 cameraTarget_;
	Vector3 cameraDirection_;
};

