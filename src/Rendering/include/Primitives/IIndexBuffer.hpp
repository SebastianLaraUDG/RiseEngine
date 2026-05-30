#pragma once
#include <RiseEngineCore/Core/CoreTypes.hpp>
#include <Rendering/include/RHIDefinitions.hpp>

namespace RiseEngine::Rendering
{
	/*
	* IBO interface, platform agnostic.
	*/
	class IIndexBuffer
	{
	public:

		virtual ~IIndexBuffer() = default;
		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;
		virtual uint32 GetCount() const = 0;
		virtual EBufferFrequency GetFrequency() const = 0;
		virtual EBufferAccess GetAccess() const = 0;
	};
}