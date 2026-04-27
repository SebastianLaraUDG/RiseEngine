#include "Application.hpp"
#include <glad/glad.h>
#include <vendor/OpenGL/GLFW/include/GLFW/glfw3.h>
#include "Rendering/include/Renderer.hpp"
#include <Rendering/include/Shader.hpp>
#include "Core/FileSystem.hpp"
#include <iostream>
/*
TODO:
* Set ESCAPE key to close window.
* Set TAB key to switch between wireframe and fill mode.
*/
using Application = RiseEngine::Application;

Application::Application() : Application(800, 600, "Rise Engine")
{
}

Application::Application(int32 windowWidth, int32 windowHeight, const char* title) : deltaTime_(0.0), lastFrame(std::chrono::steady_clock::now())
{
	Init(windowWidth, windowHeight, title);
}

Application::~Application()
{
	glfwTerminate();
}


void Application::Run()
{
	// Loop
	while (!glfwWindowShouldClose(window_.get()->GetGLFWWindow()))
	{
		Update();
		Render();
		ProcessInput();
	}
	// optional: de-allocate all resources once they've outlived their purpose:
	// ------------------------------------------------------------------------
}

void Application::Update()
{
	// Calculate delta time.
	auto currentFrame = std::chrono::steady_clock::now();
	std::chrono::duration<f64> elapsed = currentFrame - lastFrame;
	f64 deltaTime = elapsed.count();
	lastFrame = currentFrame;

	/*
	* TODO: the update() list approach is used for now, but since the elements at the
	* beginning of the list will be updated before the ones at the end, I 
	* should implement a different approach like the Double Buffer pattern.
	*/
}

void Application::Render() const
{
	renderer_->Clear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Draw here
	shader_->Bind();
	renderer_->Draw(*vao, *vbo, *shader_);
}

void Application::ProcessInput()
{
	window_->SwapBuffers();
	window_->PollEvents();	
}

void RiseEngine::Application::Init(int32 width, int32 height, const char* title)
{
	// Initialize GLFW.
	if (!glfwInit())
	{
		std::cout << "GLFW Failed to initialize!\n";
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	// This initializes GLAD context and loads all OpenGL function pointers. Note that GLAD should be initialized after creating a window and making its context current.
	window_ = std::make_unique<Window>(width, height, title);

	renderer_ = std::make_unique<Renderer>();
	renderer_->SetCapacityEnabled(GL_DEPTH_TEST, true);

	InitFileSystem();

	shader_ = std::make_unique<Shader>(
		FileSystem::Resolve("engine://assets/shaders/Basic2DTriangle/VertexShader.glsl").string(),
		FileSystem::Resolve("engine://assets/shaders/Basic2DTriangle/FragmentShader.glsl").string()
	);

	vao = std::make_unique<VAO>();
	vbo = std::make_unique<VBO>();

	const std::vector<f32> vertices =
	{
		-0.5f, 0.0f, 0.0f, /*Color*/ 1.0f, 0.0f, 0.0f, 1.0f,
		0.0f,0.5f,0.0f,				0.0f, 1.0f, 0.0f, 1.0f,
		0.5f, 0.0f, 0.0f,				0.0f, 0.0f, 1.0f, 1.0f
	};

	vbo->SetData<f32>(GL_ARRAY_BUFFER, vertices, GL_STATIC_DRAW);
	vao->SetLayout(7, 0, 3, GL_FLOAT, GL_FALSE);
	vao->SetLayout(7, 1, 4, GL_FLOAT, GL_FALSE, (void*)(3 * sizeof(f32)));

}

void RiseEngine::Application::InitFileSystem()
{
	FileSystem::SetEngineRoot(
		std::filesystem::path(__FILE__).parent_path().parent_path() // // It is currently being assumed to RiseEngine folder.
	);
	FileSystem::SetGameRoot(
		std::filesystem::current_path()
	);
}
