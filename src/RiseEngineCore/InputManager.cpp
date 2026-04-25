#include <RiseEngineCore/InputManager.hpp>
#include <stdio.h>
#include <string>

InputManager::InputManager(GLFWwindow* window, const int32 mode, const int32 value)
{
	glfwSetInputMode(window, mode, value);
	
	glfwSetWindowUserPointer(window, this);
	glfwSetCursorPosCallback(window, cursorPosCallback);
	// TODO: glfwSetScrollCallback(window,)

	// Set cursor default position in the center of the window.
	int32 windowWidth, windowHeight;
	glfwGetWindowSize(window, &windowWidth, &windowHeight);
	mouseX_ = static_cast<f64>(windowWidth) * 0.5;
	mouseY_ = static_cast<f64>(windowHeight) * 0.5;
}

void InputManager::cursorPosCallback(GLFWwindow* window, f64 xpos, f64 ypos)
{
	auto instance = static_cast<InputManager*>(glfwGetWindowUserPointer(window)); // TODO: cache in some way?
	instance->HandleMouseMovement(xpos, ypos, window);
}

void InputManager::HandleMouseMovement(f64 xPos, f64 yPos, GLFWwindow* window)
{
	f64 xoffset = xPos - mouseX_;
	f64 yoffset = mouseY_ - yPos; // reversed since y-coordinates range from bottom to top
	// Set current values.
	mouseX_ = xPos;
	mouseY_ = yPos;

#if _DEBUG
	// Creamos un string con el formato deseado
	char title[150]{};
	
	switch (mouseDebugMode)
	{
	case MouseDebugMode::None: break;

	case MouseDebugMode::MouseOffset:
		sprintf_s(title, "RiseEngine | Mouse Offset: %.1f, %.1f, remove this in %s, %d", xoffset, yoffset, __FILE__, __LINE__); // Print offset values.
		break;
	case MouseDebugMode::MousePosition:
		sprintf_s(title, "RiseEngine | Mouse: %.1f, %.1f, remove this in %s, %d", mouseX_, mouseY_, __FILE__, __LINE__); // Print current mouse values.
		break;
	}

	if (mouseDebugMode != MouseDebugMode::None)
	{
		glfwSetWindowTitle(window, title);
	}
#endif
}