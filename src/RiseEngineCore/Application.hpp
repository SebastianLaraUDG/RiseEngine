#pragma once
#include <memory>

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
		class IFramebuffer;
	}

	namespace Editor
	{
		class EditorContext;
		class ViewportPanel;
	}

	namespace CommonFramework
	{
		class Entity;
	}

	class World;

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
		std::unique_ptr<Rendering::IIndexBuffer> ibo_;
		std::unique_ptr<Rendering::IVertexArray> vao_;
		std::unique_ptr<Rendering::IFramebuffer> framebuffer_;
		RenderingAPI currentRenderingAPI_ = RenderingAPI::OpenGL; // TODO: In the future (when I implement other apis after OpenGL, read this from a file and switch in Init().

		Editor::ViewportPanel* viewportPanel_ = nullptr; // Not owned by application, but by editor context.
		std::unique_ptr<Editor::EditorContext> editorContext_;
		std::unique_ptr<CommonFramework::Entity> cameraEntity_; // For testing purposes, will be removed later.
		std::unique_ptr<World> world_; // Current world/level.
	};

}