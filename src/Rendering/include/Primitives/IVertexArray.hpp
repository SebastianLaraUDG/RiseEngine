#pragma once
#include <RiseEngineCore/Core/CoreTypes.hpp>
#include <vector>
#include <Rendering/include/RHIDefinitions.hpp>

namespace RiseEngine::Rendering
{
	class IVertexBuffer;

	struct VertexAttribute
	{
		uint32 index;
		uint32 componentCount;
		RiseEngine::Rendering::EVertexDataType dataType;
		bool normalized;
		uint32 offset;
	};
	struct VertexLayout
	{
		std::vector<VertexAttribute> attributes;
		uint32 stride;
	};

	// VAO.
	class IVertexArray
	{
	public:
		virtual ~IVertexArray() = default;
		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;
		virtual void SetLayout(const VertexLayout& layout, const IVertexBuffer& vbo) = 0;
	};
}