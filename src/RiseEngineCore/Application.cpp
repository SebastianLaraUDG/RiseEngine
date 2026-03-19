#include "Application.h"
#include <Rendering/include/Shader.h>
#include <RiseEngineCore/DebugIncludes/DebugIncludes.h>
#include "Rendering/include/Renderer.h"

#include <Rendering/Shapes/Shape.h>


/*
TODO:
* Move the entire rendering pipleline to Renderer class.
* Set ESCAPE key to close window.
* Set TAB key to switch between wireframe and fill mode.
*/

Application::Application(int width, int height, const char* title)
{
	// Initialize GLFW.
	if (!glfwInit())
	{
		cout << "GLFW Failed to initialize!\n";
		glfwTerminate();
		exit(EXIT_FAILURE);
	}
	// Setup window.
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

	// Init GLEW.
	if (glewInit() != GLEW_OK)
	{
		cout << "Failed to initialize GLEW! \n";
		glfwDestroyWindow(window_);
		glfwTerminate();
		exit(EXIT_FAILURE);
	}
	glfwSetWindowUserPointer(window_, this);

	// Viewport.
	glViewport(0, 0, width, height);

	// Print GL info
#if _DEBUG
	PrintOpenGLVersionInfo();
#endif

	// Window background color. Optional
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	// TODO: glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); // Wireframe mode!
	// TODO: glPolygonMode(GL_FRONT_AND_BACK, GL_FILL); // Fill mode

	glEnable(GL_DEPTH_TEST);
	// TODO :in the future... glEnable(GL_LIGHTING);

	shape = new Shape(); // TODO: remove
	shape->PrintTransform(); // TODO: remove



	shader_ = std::make_unique<Shader>("../Rendering/Assets/Shaders/Basic2DTriangle/VertexShader.glsl",
		"../Rendering/Assets/Shaders/Basic2DTriangle/FragmentShader.glsl");
}

Application::~Application()
{
	delete shape; // TODO: remove
	glfwDestroyWindow(window_);
	glfwTerminate();
}

void Application::Run()
{
	// Loop
	while (!glfwWindowShouldClose(window_))
	{
		Update();
		Render();
	}
	// de-allocate all resources once they've outlived their purpose here
	// ------------------------------------------------------------------------
}

void Application::Update()
{
	// TODO: Input class.
	// TODO: process input.

	/*
	* TODO: the update() list approach is used for now, but since the elements at the
	* beginning of the list will be updated before the ones at the end, I 
	* should implement a different approach like the Double Buffer pattern.
	*/
}

void Application::Render() const
{
	// Clear color and depth.
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Draw here
	
	shape->render(); // TODO: remove

	/* Swap front and back buffers */
	glfwSwapBuffers(window_);
	/* Poll for and process events */
	glfwPollEvents();
}

void Application::PrintOpenGLVersionInfo()
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

void Application::framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	int windowWidth, windowHeight;
	// Update viewport
	glfwGetWindowSize(window, &windowWidth, &windowHeight);
	glViewport(0, 0, windowWidth, windowHeight);
}
