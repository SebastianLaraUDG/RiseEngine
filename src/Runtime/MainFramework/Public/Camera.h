#pragma once
#include "Entity.h"
#include <filesystem>

/*
* A first person camera.
*/
class Camera final : public Entity
{
public:
	Camera(const std::filesystem::path& jsonPath);
	~Camera() = default;

	void ProcessInput(); // To be called in the update loop.

private:
	void ProcessKeyboardInput();
	void ProcessMouseInput();

	float movementSpeed_ = 1.f;
	float rotationSpeed_ = 1.f;
};

