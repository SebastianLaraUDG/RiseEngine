#pragma once
#include <vendor/OpenGL/GLFW/include/GLFW/glfw3.h>

class InputManager
{
public:
	/*
	* @brief Set input mode for the specified window.
	*/
	explicit InputManager(GLFWwindow* window, const int mode = GLFW_CURSOR, const int value = GLFW_CURSOR_DISABLED);
	~InputManager() = default;
private:
	static void cursorPosCallback(GLFWwindow* window, double xPos, double yPos);
	void HandleMouseMovement(double xPos, double yPos);

	double mouseX_ = 0.0, mouseY_ = 0.0;
};

