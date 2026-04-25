#pragma once
#pragma warning(disable : 4251) // Remove warning C4251: class 'std::unique_ptr<...>' needs to have dll-interface to be used by clients of class '...'. This is because the unique_ptr is not exported from the DLL, but it is used in the public interface of the Window class. To fix this, we can either export the unique_ptr or we can use a raw pointer instead.
#include <memory>
#include <RiseEngineCore/Core/CoreTypes.hpp>
#include "RiseEngine.hpp"

struct GLFWwindow;
class InputManager;

class RISE_API Window
{
public:
	Window();
	Window(int32 width, int32 height, const char* title);
	~Window();

	void SwapBuffers();
	void PollEvents();

public:
	static void ResizeCallback(GLFWwindow* window, int32 width, int32 height);
	static void PrintOpenGLVersion();

public:
	// inline GLFWwindow* GetGLFWWindow() const { return glfwWindow_.get(); }
	inline GLFWwindow* const GetGLFWWindow() const { return glfwWindow_; }

private:
	void SetupWindow(int32 width, int32 height, const char* title);

private:
	// std::unique_ptr<GLFWwindow> glfwWindow_;
	GLFWwindow* glfwWindow_;
	std::unique_ptr<InputManager> inputManager_;
};

