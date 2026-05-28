#pragma once
#include <RiseEngineCore/Core/CoreTypes.hpp>

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
	};
}