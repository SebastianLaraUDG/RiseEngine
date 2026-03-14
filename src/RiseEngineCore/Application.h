#pragma once
#include "RiseEngineCore/Core/CoreCommon.h"
#include "RiseEngineCore/Core/Core.h"
#include <GL/glew.h>
#include <../src/vendor/OpenGL/GLFW/include/GLFW/glfw3.h>
#include <memory>

class RISE_ENGINE_API Application
{
public:
	Application(int width,int height, const char* title);
	~Application();

	void Run();
	void Update();
	void Render() const;

	static void PrintOpenGLVersionInfo();

private:
	// TODO: necessary? bool bShouldStop_ = false;
	
	// Window
	GLFWwindow* window_;

	// Callback for framebuffer size.
	static void framebuffer_size_callback(GLFWwindow* window, int width, int height);

	class Shape* shape; // REMOVE
};

