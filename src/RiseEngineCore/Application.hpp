#pragma once
#include <memory>

#include <RiseEngineCore/Core/CoreCommon.hpp>
#pragma warning(disable : 4251) // Remove warning C4251: class 'std::unique_ptr<...>' needs to have dll-interface to be used by clients of class '...'. This is because the unique_ptr is not exported from the DLL, but it is used in the public interface of the Application class. To fix this, we can either export the unique_ptr or we can use a raw pointer instead.
#include <RiseEngineCore/Window.hpp>
#include <chrono>

#include "RiseEngine.hpp"


namespace RiseEngine
{
	namespace Rendering
	{
		class IRHI;
		class IShader;
		class IVertexBuffer;
		class IVertexArray;
		class IIndexBuffer;
	}

	enum class RenderingAPI
	{
		OpenGL,
		DirectX11,
		DirectX12,
		Vulkan // I am scared just by seeing this...
	};

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
		void Init(int32 width, int32 height, const char* title);
		void InitFileSystem();

	private:

		std::unique_ptr<Window> window_;
		std::unique_ptr<Rendering::IRHI> rhi_;
		std::unique_ptr<Rendering::IShader> shader_;
		std::unique_ptr<Rendering::IVertexBuffer> vbo_;
		std::unique_ptr<Rendering::IVertexArray> vao_;
		std::unique_ptr<Rendering::IIndexBuffer> ibo_;
		RenderingAPI currentAPI_ = RenderingAPI::OpenGL; // TODO: In the future (when I implement other apis after OpenGL, read this from a file and switch in Init().

		// Time management.
		std::chrono::steady_clock::time_point lastFrame;
		f64 deltaTime_; // Time between current frame and last frame.
	};

}