<<<<<<< Updated upstream
#include "Application.h"
#include <Rendering/include/Shader.h>
#include <RiseEngineCore/DebugIncludes/DebugIncludes.h>
#include "Rendering/include/Renderer.h"
=======
#include "Application.hpp"
#include <vendor/OpenGL/GLFW/include/GLFW/glfw3.h>
#include "Rendering/include/Renderer.hpp"
#include <Rendering/include/Shader.hpp>
#include "Core/FileSystem.hpp"
#include <iostream>
>>>>>>> Stashed changes

/*
TODO:
* Set ESCAPE key to close window.
* Set TAB key to switch between wireframe and fill mode.
*/
using Application = RiseEngine::Application;

<<<<<<< Updated upstream
Application::Application(int width, int height, const char* title)
=======
Application::Application(int32 windowWidth, int32 windowHeight, const char* title) : deltaTime_(0.0)
>>>>>>> Stashed changes
{
	// Create renderer
	renderer_ = new Renderer();

	// Initialize GLFW.
	if (!glfwInit())
	{
		std::cout << "GLFW Failed to initialize!\n";
		glfwTerminate();
		exit(EXIT_FAILURE);
	}
<<<<<<< Updated upstream
	// Configure.
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Create window
	window_ = glfwCreateWindow(width, height, title, NULL, NULL);

	// OPTIONAL Get window frame size: glfwGetFramebufferSize(window,)

	// Set context.
	glfwMakeContextCurrent(window_);

	// Set callback for the frambebuffer size.
	glfwSetFramebufferSizeCallback(window_, framebuffer_size_callback);
=======
	
	window_ = std::make_unique<Window>(windowWidth, windowHeight, title);
>>>>>>> Stashed changes

	// Init GLEW.
	if (glewInit() != GLEW_OK)
	{
		std::cout << "Failed to initialize GLEW! \n";
		glfwTerminate();
		exit(EXIT_FAILURE);
	}
	glfwSetWindowUserPointer(window_, this);

	renderer_ = std::make_unique<Renderer>();

	InitFileSystem();

	shader_ = std::make_unique<Shader>(
		FileSystem::Resolve("engine://assets/shaders/Basic2DTriangle/VertexShader.glsl").string(),
		FileSystem::Resolve("engine://assets/shaders/Basic2DTriangle/FragmentShader.glsl").string()
	);

<<<<<<< Updated upstream
	glEnable(GL_DEPTH_TEST);
=======
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
>>>>>>> Stashed changes
}

Application::~Application()
{
<<<<<<< Updated upstream
	delete renderer_;
	delete triangleShader;
	glfwDestroyWindow(window_);
=======
>>>>>>> Stashed changes
	glfwTerminate();
}


void Application::Run()
{
<<<<<<< Updated upstream
	// TODO: for now I will have a simple triangle here in the run method
	const float VERTICES_DATA[] =
	{
		// XYZ				|| Vertex color (RGBA)
		-1.0f,+0.0f,+0.0f,	1.0f,0.0f,0.0f,1.0f,
		+0.0f,+1.0f,+0.0f,	0.0f,1.0f,0.0f,1.0f,
		+1.0f,+0.0f,+0.0f,	0.0f,0.0f,1.0f,1.0f
	};
	// 3 For position + 4 for color.
	const int DATA_ROW_SIZE = 7;
	
	
	triangleShader = new Shader(
		"../Rendering/Assets/Shaders/Basic2DTriangle/VertexShader.glsl",
		"../Rendering/Assets/Shaders/Basic2DTriangle/FragmentShader.glsl"
		);
	
	glGenVertexArrays(1, &VAO_);
	glGenBuffers(1, &VBO_);
	// Binding
	glBindVertexArray(VAO_);
	glBindBuffer(GL_ARRAY_BUFFER, VBO_);
	glBufferData(GL_ARRAY_BUFFER, sizeof(VERTICES_DATA), VERTICES_DATA, GL_STATIC_DRAW);

	// Position attribute
	int32 stride = sizeof(float) * DATA_ROW_SIZE;
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, stride, (void*)0);
	glEnableVertexAttribArray(0);
	// Color attribute
	glVertexAttribPointer(1, 4, GL_FLOAT, GL_FALSE, stride, (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);


=======
	static float increaseFactor = 0.05f;
>>>>>>> Stashed changes
	// Loop
	while (!glfwWindowShouldClose(window_.get()->GetGLFWWindow()))
	{
		Update();
		Render();
		ProcessInput();
	}
	// optional: de-allocate all resources once they've outlived their purpose:
	// ------------------------------------------------------------------------
	glDeleteVertexArrays(1, &VAO_);
	glDeleteBuffers(1, &VBO_);
}

void Application::Update()
{
<<<<<<< Updated upstream
	// TODO: Input class.
	// TODO: process input.
=======
	/*
	* TODO: the update() list approach is used for now, but since the elements at the
	* beginning of the list will be updated before the ones at the end, I 
	* should implement a different approach like the Double Buffer pattern.
	*/
>>>>>>> Stashed changes
}

void Application::Render() const
{
	renderer_->Clear();

<<<<<<< Updated upstream
	// TODO: Draw here
	
	triangleShader->use();
	// glBindVertexArray(VAO_); TODO: necessary?
	glDrawArrays(GL_TRIANGLES, 0, 3); // Un-Optimal drawing method, but the appropriate since I am drawing
									  // one single triangle. To draw multiple triangles that share vertices
									  // I should use glDrawElements();

	/* Swap front and back buffers */
	glfwSwapBuffers(window_);
	/* Poll for and process events */
	glfwPollEvents();
=======
	// Draw here
	shader_->Bind();
	renderer_->Draw(*vao, *vbo, *shader_);
>>>>>>> Stashed changes
}

void Application::ProcessInput()
{
	window_->SwapBuffers();
	window_->PollEvents();	
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
