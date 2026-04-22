#pragma once
#include "Core/CoreTypes.hpp"
#include <vendor/OpenGL/GLFW/include/GLFW/glfw3.h>

// TODO: make this class a singleton?
class InputManager
{
public:
	/*
	* @brief Set input mode for the specified window.
	*/
	explicit InputManager(GLFWwindow* window, int32 mode = GLFW_CURSOR, int32 value = GLFW_CURSOR_DISABLED);
	~InputManager() = default;
private:
	static void cursorPosCallback(GLFWwindow* window, f64 xPos, f64 yPos);
	void HandleMouseMovement(f64 xPos, f64 yPos, GLFWwindow* window);

	f64 mouseX_ = 0.0, mouseY_ = 0.0;
};

