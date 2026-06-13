#include "Application.hpp"
#include <vendor/OpenGL/GLFW/include/GLFW/glfw3.h>
#include "Core/FileSystem.hpp"
#include <Rendering/OpenGL/OpenGLRHI.hpp>
#include <Rendering/include/Primitives/IShader.hpp>
#include <Rendering/include/Primitives/IVertexArray.hpp>
#include <Rendering/include/Primitives/IVertexBuffer.hpp>
#include <Rendering/include/Primitives/IIndexBuffer.hpp>
#include <Rendering/include/Primitives/IFramebuffer.hpp>
#include <RiseEngineCore/Editor/Panels/ViewportPanel.hpp>
#include <iostream>

#include <CommonFramework/WorldObjects/Entity.hpp>
#include <CommonFramework/Components/CameraComponent.hpp>

#include <vendor/imgui/imgui.h>
#include <RiseEngineCore/Editor/EditorContext.hpp>

#include "Core/Time.hpp"

#include "Runtime/World/World.hpp"
#include "Runtime/World/WorldManager.hpp"

/*
TODO:
* Set ESCAPE key to close window.
* Set TAB key to switch between wireframe and fill mode.
*/

using namespace RiseEngine;

Application::Application() : Application(800, 600, "Rise Engine")
{
}

Application::Application(int32 windowWidth, int32 windowHeight, const char* title)
{
	Init(windowWidth, windowHeight, title);
}

Application::~Application()
{
	rhi_->ShutdownImGui(); // First renderer backend.
	editorContext_->Shutdown(); // Next destroy context.
	WorldManager::Shutdown();
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
	RiseEngine::Time::Update();

	if (WorldManager::HasActiveWorld())
		WorldManager::GetActiveWorld()->Update(Time::GetDeltaTime32()); // TODO: implement double buffer or fixed update. World Update() currently updates every entity in the vector, but that gives advantage to entities at the beginning of the vector.

	/*
	* TODO: the update() list approach is used for now, but since the elements at the
	* beginning of the list will be updated before the ones at the end, I 
	* should implement a different approach like the Double Buffer pattern.
	*/
}

void Application::Render() const
{
	using namespace RiseEngine::Rendering;
	
	// Resize framebuffer if viewport changed.
	if (viewportPanel_->WasResized())
	{
		glm::vec2 size = viewportPanel_->GetViewportSize();
		framebuffer_->Resize(static_cast<uint32>(size.x), static_cast<uint32>(size.y));
	}

	framebuffer_->Bind();
	rhi_->Clear(EClearFlags::Color | EClearFlags::Depth);

	// Temporary: only one camera.
	auto camera = cameraEntity_->GetComponent<CommonFramework::CameraComponent>();
	
	// Draw here
	shader_->Bind();
	shader_->SetMat4("uViewProjection", camera->GetViewProjection());

	vao_->Bind();
	ibo_->Bind();
	// rhi_->DrawPrimitive(3); // USING VAO
	rhi_->SetPolygonMode(EPolygonMode::Wireframe);
	rhi_->DrawIndexed(ibo_->GetCount());

	framebuffer_->Unbind();

	// ImGui. - render to screen, not the framebuffer.
	rhi_->BeginImGuiFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();
	editorContext_->RenderPanels(); // ViewportPanel displays the framebuffer texture here.
	ImGui::Render();
	rhi_->EndImGuiFrame();
}

void Application::ProcessInput()
{
	window_->SwapBuffers();
	window_->PollEvents();	
}

void Application::Init(int32 width, int32 height, const char* title)
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

	switch(currentRenderingAPI_)
	{
		case RenderingAPI::OpenGL:
			rhi_ = std::make_unique<Rendering::OpenGL::OpenGLRHI>(); // TODO: in the future when I learn DirectX11 and 12 setup in a config or somehow.
			break;
	}
	rhi_->Init();

	InitFileSystem();

	shader_ = rhi_->CreateShader(
		FileSystem::Resolve("engine://assets/shaders/Quad3D Perspective/Quad3D_VS.glsl").string(), // Basic2DTriangle/VertexShader.glsl
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
	vbo_ = rhi_->CreateVertexBuffer(quadVertices.data(), static_cast<uint32>(quadVertices.size() * sizeof(f32))); // Quad.
	ibo_ = rhi_->CreateIndexBuffer(quadIndices.data(), static_cast<uint32>(quadIndices.size()));
	
	Rendering::VertexLayout layout;
	layout.stride = 7 * sizeof(f32);
	layout.attributes =
	{
		{0, 3, Rendering::EVertexDataType::Float, false, 0}, // pos
		{1, 4, Rendering::EVertexDataType::Float, false, 3 * sizeof(f32)} // color.
	};

	vao_ = rhi_->CreateVertexArray();
	vao_->SetLayout(layout, *vbo_);

	cameraEntity_ = std::make_unique<CommonFramework::Entity>("Camera");
	auto* camera = cameraEntity_->AddComponent<CommonFramework::CameraComponent>(45.f, 800.f/600.f, 0.1f, 100.f);
	camera->SetLocalPosition({ 0.f, 0.f, 25.f });

	// Init editor (IMGUI).
	editorContext_ = std::make_unique<Editor::EditorContext>();
	editorContext_->Init(window_->GetGLFWWindow());
	rhi_->InitImGui();

	Rendering::FramebufferSpec spec;
	spec.width = width;
	spec.height = height;
	framebuffer_ = rhi_->CreateFramebuffer(spec);

	// Create viewport panel and register.
	viewportPanel_ = editorContext_->AddPanel<Editor::ViewportPanel>(framebuffer_.get());

	
	WorldManager::Init();
	WorldManager::GetActiveWorld()->CreateEntity();
}

void Application::InitFileSystem()
{
	FileSystem::SetEngineRoot(
		std::filesystem::path(__FILE__).parent_path().parent_path() // // It is currently being assumed to RiseEngine folder.
	);
	FileSystem::SetGameRoot(
		std::filesystem::current_path()
	);
}
