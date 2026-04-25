#pragma once
#include <memory>

#include <RiseEngineCore/Core/CoreCommon.hpp>
#pragma warning(disable : 4251) // Remove warning C4251: class 'std::unique_ptr<...>' needs to have dll-interface to be used by clients of class '...'. This is because the unique_ptr is not exported from the DLL, but it is used in the public interface of the Application class. To fix this, we can either export the unique_ptr or we can use a raw pointer instead.
#include <RiseEngineCore/Window.hpp>
#include <Rendering/include/Renderer.hpp>
#include <Rendering/include/VAO.hpp>
#include <Rendering/include/VBO.hpp>

#include "RiseEngine.hpp"

namespace RiseEngine
{

	class RISE_API Application
	{
	public:
		Application();
		explicit Application(int32 windowWidth, int32 windowHeight, const char* title);
		virtual ~Application();

		void Run();
	protected:
		void Update();
		void Render() const;
		void ProcessInput();

	protected:
		void InitFileSystem();

	private:

		std::unique_ptr<Window> window_;
		std::unique_ptr<Renderer> renderer_;

		std::unique_ptr<Shader> shader_; // The unique global shader of the program.

		/* Temporal, remove. */
		std::unique_ptr<VAO> vao;
		std::unique_ptr<VBO> vbo;

		double deltaTime_; // Time between current frame and last frame.
	};

}