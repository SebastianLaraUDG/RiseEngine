#pragma once
#include <Rendering/include/IRHI.hpp>
#include <Rendering/include/RHIDefinitions.hpp>

namespace RiseEngine::Rendering::OpenGL
{
	/*
	* OpenGL Rendering Hardware interface.
	* Only uses OpenGL Core profile.
	*/
	class OpenGLRHI : public IRHI
	{
		using EClearFlags = RiseEngine::Rendering::EClearFlags;

	public:
		void Init() override;
		void Shutdown() override;
		void SetClearColor(f32 r, f32 g, f32 b, f32 a) override;
		void Clear(EClearFlags flags) override;
		void SetPolygonMode(EPolygonMode mode) override;
		void DrawPrimitive(uint32 vertexCount, EPrimitiveType primitiveType = EPrimitiveType::Triangles, uint32 startVertex = 0) override;
		// TODO: for now it is assumed that the indices are GL_UNSIGNED_INT.
		void DrawIndexed(uint32 indexCount, EPrimitiveType primitiveType = EPrimitiveType::Triangles, uint32 startIndex = 0) override;

		// Factory methods. RHI creates its own resources.
		std::unique_ptr<IVertexArray> CreateVertexArray() override;

		std::unique_ptr<IVertexBuffer> CreateVertexBuffer(const void* data, uint32 size,
			EBufferFrequency frequency = EBufferFrequency::Static,
			EBufferAccess access = EBufferAccess::Draw) override;
		
		std::unique_ptr<IIndexBuffer> CreateIndexBuffer(const uint32* indices, uint32 count,
			EBufferFrequency frequency = EBufferFrequency::Static,
			EBufferAccess access = EBufferAccess::Draw) override;

		std::unique_ptr<IShader> CreateShader(const std::string& vertPath, const std::string& fragPath) override;


	private:
		// Converts the supplied type to an OpenGL type (like GL_TRIANGLES, etc.).
		static uint32 TranslatePrimitive(EPrimitiveType primitiveType);
	};
}