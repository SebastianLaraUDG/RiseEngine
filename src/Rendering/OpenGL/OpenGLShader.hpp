#pragma once
#include <Rendering/include/Primitives/IShader.hpp>

namespace RiseEngine::Rendering
{
	class OpenGLShader : public IShader
	{
	public:
		OpenGLShader(const std::string& vertexPath, const std::string& fragmentPath);
		~OpenGLShader() override;

		void Bind() const override;
		void Unbind() const override;

		void SetInt(const std::string& name, int32 value) override;
		void SetFloat(const std::string& name, f32 value) override;
		void SetDouble(const std::string& name, f64 value) override;
		void SetVec3(const std::string& name, const glm::vec3& value) override;
		void SetVec4(const std::string& name, const glm::vec4& value) override;
		void SetMat4(const std::string& name, const glm::mat4& value) override;
	
	private:
		int32 GetUniformLocation(const std::string& name) const;
		static uint32 CompileShader(uint32 shaderType, const std::string& source);
		static uint32 LinkProgram(uint32 vertexShader, uint32 fragmentShader);
		static bool CheckStatus(uint32 object,
			std::function<void(uint32, uint32, int32*)> getIV,
			uint32 statusToCheck,
			std::function<void(uint32, int32, int32*, char*)> getInfoLog);
	
	private:
		uint32 id_;
		mutable std::unordered_map<std::string, int32> uniformLocationCache_;
	};
}