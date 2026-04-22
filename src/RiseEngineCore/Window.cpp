#include "Window.hpp"
#include <iostream>

Window::Window(int32 width, int32 height, const char* title)
{
	// Setup window.
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// OPTIONAL Get window frame size // glfwGetFramebufferSize(window,)

	// Create the glfw window object.
	glfwWindow_ = glfwCreateWindow(width, height, title, NULL, NULL);

	// glfwMakeContextCurrent(glfwWindow_.get());
	// glfwSetFramebufferSizeCallback(glfwWindow_.get(), ResizeCallback);
	glfwMakeContextCurrent(glfwWindow_);
	glfwSetFramebufferSizeCallback(glfwWindow_, ResizeCallback);

	// Viewport.
	glViewport(0, 0, width, height);

#if _DEBUG
	// Print OpenGL info.
	PrintOpenGLVersion();
#endif

	// Create the input manager.
	inputManager_ = std::make_unique<InputManager>(glfwWindow_,GLFW_CURSOR, GLFW_CURSOR_NORMAL);
	// TODO: setup input manager
}

Window::~Window()
{
	// glfwDestroyWindow(glfwWindow_.get());
	glfwDestroyWindow(glfwWindow_);
}

void Window::SwapBuffers()
{
	/* Swap front and back buffers */
	// glfwSwapBuffers(glfwWindow_.get());
	glfwSwapBuffers(glfwWindow_);
}

void Window::PollEvents()
{
	/* Poll for and process events */
	glfwPollEvents();
}

void Window::ResizeCallback(GLFWwindow* window, int32 width, int32 height)
{
	auto self = static_cast<Window*>(glfwGetWindowUserPointer(window));
	if (self) {
		int32 windowWidth, windowHeight;
		// Update viewport.
		glfwGetWindowSize(window, &windowWidth, &windowHeight);
		glViewport(0, 0, windowWidth, windowHeight);
	}
}

void Window::PrintOpenGLVersion()
{
	// Print GL version
	std::cout << "Version: " << glGetString(GL_VERSION) << "\n";
	// Print vendor
	std::cout << "Vendor: " << glGetString(GL_VENDOR) << "\n";
	// Print renderer
	std::cout << "Renderer: " << glGetString(GL_RENDERER) << "\n";
	// Print shading language
	std::cout << "Shading language: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << "\n";
}
