#pragma once
#include <RiseEngineCore/Core.h>
#include <Rendering/include/Renderer.h>
#include <../src/vendor/OpenGL/GLFW/include/GLFW/glfw3.h>


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
	class Shader* triangleShader;// TODO: remove. This is temporal. There should be a way to store many shader.
	uint VAO_,VBO_; // TODO: remove.

	Renderer* renderer_;
	
	// Window
	GLFWwindow* window_;

	// Callback for framebuffer size.
	static void framebuffer_size_callback(GLFWwindow* window, int width, int height);
};

