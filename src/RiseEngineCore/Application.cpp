#include "Application.h"
#include <Rendering/include/Shader.h>
#include <RiseEngineCore/DebugIncludes/DebugIncludes.h>
#include "Rendering/include/Renderer.h"

/*
TODO:
* Move the entire rendering pipleline to Renderer class.
* Set ESCAPE key to close window.
* Set TAB key to switch between wireframe and fill mode.
*/

Application::Application(int width, int height, const char* title)
{
	// Create renderer
	renderer_ = new Renderer();

	// Initialize GLFW.
	if (!glfwInit())
	{
		cout << "GLFW Failed to initialize!\n";
		glfwTerminate();
		exit(EXIT_FAILURE);
	}
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
}

Application::~Application()
{
	delete renderer_;
	delete triangleShader;
	glfwDestroyWindow(window_);
	glfwTerminate();
}

void Application::Run()
{
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


	// Loop
	while (!glfwWindowShouldClose(window_))
	{
		Update();
		Render();
	}
	// optional: de-allocate all resources once they've outlived their purpose:
	// ------------------------------------------------------------------------
	glDeleteVertexArrays(1, &VAO_);
	glDeleteBuffers(1, &VBO_);
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
