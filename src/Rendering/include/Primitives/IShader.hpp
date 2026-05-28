#pragma once
#include <string>
#include <RiseEngineCore/Core/CoreTypes.hpp>
#include <vendor/glm/glm.hpp>

namespace RiseEngine::Rendering
{
	// Platfomr-agnostic shader.
	class IShader
	{
	public:
		virtual ~IShader() = default;
		virtual void Bind() const = 0;
		virtual void Unbind() const = 0;

		virtual void SetInt(const std::string& name, int32 value) = 0;
		virtual void SetFloat(const std::string& name, f32 value) = 0;
		virtual void SetDouble(const std::string& name, f64 value) = 0;
		virtual void SetVec3(const std::string& name, const glm::vec3& value) = 0;
		virtual void SetVec4(const std::string& name, const glm::vec4& value) = 0;
		virtual void SetMat4(const std::string& name, const glm::mat4& value) = 0;
	};
}