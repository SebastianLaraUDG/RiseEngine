#include "InputManager.h"


InputManager::InputManager(GLFWwindow* window, const int mode, const int value)
{
	glfwSetInputMode(window, mode, value);
	
	glfwSetCursorPosCallback(window, cursorPosCallback);

	// Set cursor default position in the middle of the window.
	int windowWidth, windowHeight;
	glfwGetWindowSize(window, &windowWidth, &windowHeight);
	mouseX_ = static_cast<double>(windowWidth) / 2;
	mouseY_ = static_cast<double>(windowHeight) / 2;
}

void InputManager::cursorPosCallback(GLFWwindow* window, double xpos, double ypos)
{
	auto* instance = static_cast<InputManager*>(glfwGetWindowUserPointer(window));
}

#include <iostream> // TODO: remove

void InputManager::HandleMouseMovement(double xPos, double yPos)
{
	double xoffset = xPos - mouseX_;
	double yoffset = mouseY_ - yPos; // reversed since y-coordinates range from bottom to top
	// Set current values.
	mouseX_ = xPos;
	mouseY_ = yPos;

	std::cout << "Position x current:" << mouseX_ << std::endl;
	std::cout << "Position y current:" << mouseY_ << std::endl;
}