#pragma once
#include <Rendering/include/RHIDefinitions.hpp>
#include <memory>
#include <string>
#include "Primitives/IFramebuffer.hpp"

namespace RiseEngine::Rendering
{
	// Forward declarations.
	class IVertexArray;
	class IVertexBuffer;
	class IIndexBuffer;
	class IShader;
	class IFramebuffer;

	class IRHI
	{
	public:
		virtual ~IRHI() = default;

		virtual void Init() = 0;
		virtual void Shutdown() = 0;

		virtual void InitImGui() = 0;
		virtual void ShutdownImGui() = 0;
		virtual void BeginImGuiFrame() = 0;
		virtual void EndImGuiFrame() = 0;

		virtual void SetClearColor(f32 r, f32 g, f32 b, f32 a) = 0;
		virtual void Clear(RiseEngine::Rendering::EClearFlags flags) = 0;
		virtual void SetPolygonMode(RiseEngine::Rendering::EPolygonMode mode) = 0;

		virtual void DrawPrimitive(uint32 vertexCount, EPrimitiveType primitiveType = EPrimitiveType::Triangles, uint32 startVertex = 0) = 0;
		virtual void DrawIndexed(uint32 vertexCount, EPrimitiveType primitiveType = EPrimitiveType::Triangles, uint32 startVertex = 0) = 0;

		// Factory methods. RHI creates its own resources.
		virtual std::unique_ptr<IVertexArray> CreateVertexArray() = 0;
		
		// @param size - in bytes.
		virtual std::unique_ptr<IVertexBuffer> CreateVertexBuffer(const void* data, uint32 size,
			EBufferFrequency frequency = EBufferFrequency::Static,
			EBufferAccess access = EBufferAccess::Draw) = 0;
		
		virtual std::unique_ptr<IIndexBuffer> CreateIndexBuffer(const uint32* indices, uint32 count,
			EBufferFrequency frequency = EBufferFrequency::Static,
			EBufferAccess access = EBufferAccess::Draw) = 0;
		
		// Shaders.

		virtual std::unique_ptr<IShader> CreateShader(const std::string& vertPath, const std::string& fragPath) = 0;

		
		// Framebuffers.

		virtual std::unique_ptr<IFramebuffer> CreateFramebuffer(const FramebufferSpec& spec) = 0;
	};
}