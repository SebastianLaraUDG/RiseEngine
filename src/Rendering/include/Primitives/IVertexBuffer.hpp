#pragma once
#include <RiseEngineCore/Core/CoreTypes.hpp>
#include <Rendering/include/RHIDefinitions.hpp>

namespace RiseEngine::Rendering
{
	/*
	* VBO interface, platform agnostic.
	*/
	class IVertexBuffer
	{
	public:
		using EBufferFrequency = RiseEngine::Rendering::EBufferFrequency;
		using EBufferAccess = RiseEngine::Rendering::EBufferAccess;

		virtual ~IVertexBuffer() = default;
		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;
		virtual void SetData(const void* data, uint32 size) = 0;
		virtual EBufferFrequency GetFrequency() const = 0;
		virtual EBufferAccess GetAccess() const = 0;
	};
}