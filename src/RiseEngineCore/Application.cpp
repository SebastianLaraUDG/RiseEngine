#include "Application.hpp"
#include <vendor/OpenGL/GLFW/include/GLFW/glfw3.h>
#include "Core/FileSystem.hpp"
#include <Rendering/OpenGL/OpenGLRHI.hpp>
#include <Rendering/include/Primitives/IShader.hpp>
#include <Rendering/include/Primitives/IVertexArray.hpp>
#include <Rendering/include/Primitives/IVertexBuffer.hpp>
#include <Rendering/include/Primitives/IIndexBuffer.hpp>
#include <iostream>
/*
TODO:
* Set ESCAPE key to close window.
* Set TAB key to switch between wireframe and fill mode.
*/

using namespace RiseEngine;

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
	using namespace RiseEngine::Rendering;
	rhi_->Clear(EClearFlags::Color | EClearFlags::Depth);

	// Draw here
	shader_->Bind();
	vao_->Bind();
	ibo_->Bind();
	// rhi_->DrawPrimitive(3); // USING VAO
	rhi_->DrawIndexed(ibo_->GetCount());
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

	switch(currentAPI_)
	{
		case RenderingAPI::OpenGL:
			rhi_ = std::make_unique<Rendering::OpenGL::OpenGLRHI>(); // TODO: in the future when I learn DirectX11 and 12 setup in a config or somehow.
			break;
	}
	rhi_->Init();

	InitFileSystem();

	shader_ = rhi_->CreateShader(
		FileSystem::Resolve("engine://assets/shaders/Basic2DTriangle/VertexShader.glsl").string(),
		FileSystem::Resolve("engine://assets/shaders/Basic2DTriangle/FragmentShader.glsl").string()
	);

	const std::vector<f32> triangleVertices =
	{
		-0.5f, 0.0f, 0.0f, /*Color*/ 1.0f, 0.0f, 0.0f, 1.0f,
		0.0f,0.5f,0.0f,				0.0f, 1.0f, 0.0f, 1.0f,
		0.5f, 0.0f, 0.0f,				0.0f, 0.0f, 1.0f, 1.0f
	};

	const std::vector<f32> quadVertices =
	{
		// pos                  // color
	-0.5f, -0.5f, 0.0f,   1.0f, 0.0f, 0.0f, 1.0f,  // bottom left
	 0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f, 1.0f,  // bottom right
	 0.5f,  0.5f, 0.0f,   0.0f, 0.0f, 1.0f, 1.0f,  // top right
	-0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f, 1.0f,  // top left
	};

	const std::vector<uint32> quadIndices =
	{
		0, 1, 2, // first triangle
		2, 3, 0  // second triangle
	};

	// vbo_ = rhi_->CreateVertexBuffer(triangleVertices.data(), triangleVertices.size() * sizeof(f32)); Triangle.
	vbo_ = rhi_->CreateVertexBuffer(quadVertices.data(), quadVertices.size() * sizeof(f32)); // Quad.
	ibo_ = rhi_->CreateIndexBuffer(quadIndices.data(), quadIndices.size());
	
	Rendering::VertexLayout layout;
	layout.stride = 7 * sizeof(f32);
	layout.attributes =
	{
		{0, 3, Rendering::EVertexDataType::Float, false, 0}, // pos
		{1, 4, Rendering::EVertexDataType::Float, false, 3 * sizeof(f32)} // color.
	};

	vao_ = rhi_->CreateVertexArray();
	vao_->SetLayout(layout, *vbo_);
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
