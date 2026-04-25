#pragma once
#include "Core/CoreTypes.hpp"

struct GLFWwindow;

enum class MouseDebugMode
{
	None,
	MouseOffset,
	MousePosition
};


struct GLFWwindow;

// TODO: make this class a singleton?
class InputManager
{
public:
	/*
	* @brief Set input mode for the specified window.
	* @param Window
	* @param mode - GLFW_CURSOR commonly.
	* @param value - GLFW_CURSOR_DISABLED or GLFW_CURSOR_NORMAL commonly.
	*/
	explicit InputManager(GLFWwindow* window, int32 mode, int32 value);
	~InputManager();

public:
	MouseDebugMode mouseDebugMode = MouseDebugMode::None;

private:
	static void cursorPosCallback(GLFWwindow* window, f64 xPos, f64 yPos);
	void HandleMouseMovement(f64 xPos, f64 yPos, GLFWwindow* window);

	f64 mouseX_ = 0.0, mouseY_ = 0.0;
};

