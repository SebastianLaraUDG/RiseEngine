#pragma once
#include <Rendering/include/Primitives/IIndexBuffer.hpp>
namespace RiseEngine::Rendering
{
	/*
	* OpenGL implementation of the IIndexBuffer interface.
	*/
	class OpenGLIndexBuffer : public IIndexBuffer
	{
	public:
		OpenGLIndexBuffer(const uint32* indices, uint32 count, EBufferFrequency frequency = EBufferFrequency::Static, EBufferAccess access = EBufferAccess::Draw);
		~OpenGLIndexBuffer() override;

		void Bind() const override;
		void Unbind() const override;
		inline uint32 GetCount() const override { return count_; }
		inline EBufferFrequency GetFrequency() const override { return frequency_; }
		inline EBufferAccess GetAccess() const override { return access_; }

	private:
		static uint32 Translate(EBufferFrequency frequency, EBufferAccess access);

		uint32 id_;
		uint32 count_;
		EBufferFrequency frequency_;
		EBufferAccess access_;
	};
}
