#pragma once
#include <Rendering/include/Primitives/IVertexBuffer.hpp>

namespace RiseEngine::Rendering::OpenGL
{
	class OpenGLVertexBuffer : public IVertexBuffer
	{
	public:
		using EBufferFrequency = RiseEngine::Rendering::EBufferFrequency;
		using EBufferAccess = RiseEngine::Rendering::EBufferAccess;

		OpenGLVertexBuffer(const void* data, uint32 size,
			EBufferFrequency frequency = EBufferFrequency::Static,
			EBufferAccess access = EBufferAccess::Draw);
		~OpenGLVertexBuffer() override;

		void Bind() const override;
		void Unbind() const override;
		void SetData(const void* data, uint32 size) override;

		EBufferFrequency GetFrequency() const override { return frequency_; }
		EBufferAccess    GetAccess()    const override { return access_; }

	private:
		uint32 id_;

		EBufferFrequency frequency_;
		EBufferAccess access_;

		static uint32 Translate(EBufferFrequency frequency,
			EBufferAccess access);
	};
}