#include "InputManager.h"
#include <stdio.h>
#include <string>
#include <RiseEngineCore/Core/CoreTypes.h>

InputManager::InputManager(GLFWwindow* window, const int mode, const int value)
{
	glfwSetInputMode(window, mode, value);
	
	glfwSetWindowUserPointer(window, this);
	glfwSetCursorPosCallback(window, cursorPosCallback);
	// TODO: glfwSetScrollCallback(window,)

	// Set cursor default position in the middle of the window.
	int32 windowWidth, windowHeight;
	glfwGetWindowSize(window, &windowWidth, &windowHeight);
	mouseX_ = static_cast<double>(windowWidth) * 0.5;
	mouseY_ = static_cast<double>(windowHeight) * 0.5;
}

void InputManager::cursorPosCallback(GLFWwindow* window, double xpos, double ypos)
{
	auto instance = static_cast<InputManager*>(glfwGetWindowUserPointer(window)); // TODO: cache in some way?
	instance->HandleMouseMovement(xpos, ypos, window);
}

void InputManager::HandleMouseMovement(double xPos, double yPos, GLFWwindow* window)
{
	double xoffset = xPos - mouseX_;
	double yoffset = mouseY_ - yPos; // reversed since y-coordinates range from bottom to top
	// Set current values.
	mouseX_ = xPos;
	mouseY_ = yPos;

	// Creamos un string con el formato deseado
	char title[150]{};
	//sprintf_s(title, "RiseEngine | Mouse: %.1f, %.1f, remove this in %s, %d", mouseX_, mouseY_, __FILE__, __LINE__); // Print current mouse values.
	sprintf_s(title, "RiseEngine | Mouse Offset: %.1f, %.1f, remove this in %s, %d", xoffset, yoffset, __FILE__, __LINE__); // Print offset values.

	// Actualizamos el titulo de la ventana
	glfwSetWindowTitle(window, title);
}