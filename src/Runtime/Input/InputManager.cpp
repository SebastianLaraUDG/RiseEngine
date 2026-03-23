#include "InputManager.h"


InputManager::InputManager(GLFWwindow* window, const int mode, const int value)
{
	glfwSetInputMode(window, mode, value);
	
	glfwSetWindowUserPointer(window, this);
	glfwSetCursorPosCallback(window, cursorPosCallback);

	// Set cursor default position in the middle of the window.
	int windowWidth, windowHeight;
	glfwGetWindowSize(window, &windowWidth, &windowHeight);
	mouseX_ = static_cast<double>(windowWidth) / 2;
	mouseY_ = static_cast<double>(windowHeight) / 2;
}

void InputManager::cursorPosCallback(GLFWwindow* window, double xpos, double ypos)
{
	auto instance = static_cast<InputManager*>(glfwGetWindowUserPointer(window)); // TODO: cache in some way?
	instance->HandleMouseMovement(xpos, ypos, window);
}

#include <iostream> // TODO: remove

void InputManager::HandleMouseMovement(double xPos, double yPos, GLFWwindow* window)
{
	double xoffset = xPos - mouseX_;
	double yoffset = mouseY_ - yPos; // reversed since y-coordinates range from bottom to top
	// Set current values.
	mouseX_ = xPos;
	mouseY_ = yPos;

	// Creamos un string con el formato deseado
	char title[128]{};
	// sprintf_s(title, "RiseEngine | Mouse: %.1f, %.1f", mouseX_, mouseY_); // Print current mouse values.
	// sprintf_s(title, "RiseEngine | Mouse Offset: %.1f, %.1f", xoffset, yoffset); // Print offset values.

	// Actualizamos el titulo de la ventana
	// glfwSetWindowTitle(window, title);
}