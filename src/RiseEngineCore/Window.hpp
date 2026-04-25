#pragma once
#include <memory>
// #include <vendor/OpenGL/GLEW/include/GL/glew.h> // Included here to prevent glew.h(85,1): error C1189: #error:  gl.h included before glew.h
// #include <vendor/OpenGL/glad/include/glad/glad.h>
// #include <vendor/OpenGL/GLFW/include/GLFW/glfw3.h>
// #include <RiseEngineCore/InputManager.hpp>
#include "RiseEngine.hpp"

struct GLFWwindow;
class InputManager;

class RISE_API Window
{
public:
	Window();
	Window(int32 width, int32 height, const char* title);
	~Window();

	void SwapBuffers();
	void PollEvents();

public:
	static void ResizeCallback(GLFWwindow* window, int32 width, int32 height);
	static void PrintOpenGLVersion();

public:
	// inline GLFWwindow* GetGLFWWindow() const { return glfwWindow_.get(); }
	inline GLFWwindow* const GetGLFWWindow() const { return glfwWindow_; }

private:
	void SetupWindow(int32 width = 600, int32 height = 400, const char* title = "Insert name application");

private:
	// std::unique_ptr<GLFWwindow> glfwWindow_;
	GLFWwindow* glfwWindow_;
	std::unique_ptr<InputManager> inputManager_;
};

