#include "Window.hpp"
#include <glad/glad.h>
#include <vendor/OpenGL/GLFW/include/GLFW/glfw3.h>
#include <RiseEngineCore/InputManager.hpp>
#include <iostream>
#include <Rendering/include/GLErrorLibrary.hpp>

Window::Window() :Window(720, 600, "Rise Engine")
{
}

Window::Window(int32 width, int32 height, const char* title)
{
	SetupWindow(width, height, title);
}

Window::~Window()
{
	glfwDestroyWindow(glfwWindow_);
}

void Window::SwapBuffers()
{
	// Swap front and back buffers
	glfwSwapBuffers(glfwWindow_);
}

void Window::PollEvents()
{
	// Poll for and process events
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

void Window::SetupWindow(int32 width, int32 height, const char* title)
{
	// Setup window.
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// OPTIONAL Get window frame size // glfwGetFramebufferSize(window,)

	// Create the glfw window object.
	glfwWindow_ = glfwCreateWindow(width, height, title, NULL, NULL);

	glfwMakeContextCurrent(glfwWindow_);
	glfwSetFramebufferSizeCallback(glfwWindow_, ResizeCallback);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD! \n";
		// glfwTerminate(); I am not sure if this is necessary, since the destructor of the Application class will call glfwTerminate() when the window object goes out of scope. However, it is generally a good practice to clean up resources as soon as they are no longer needed, so I will leave it here for now.
		exit(EXIT_FAILURE);
	}

	// Viewport.
	glViewport(0, 0, width, height);
	
#if _DEBUG
	// Print OpenGL info.
	PrintOpenGLVersion();
#endif

	// Create the input manager.
	inputManager_ = std::make_unique<InputManager>(glfwWindow_, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
}
