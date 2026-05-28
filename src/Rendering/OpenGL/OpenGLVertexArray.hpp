#pragma once
#include <Rendering/include/Primitives/IVertexArray.hpp>

namespace RiseEngine::Rendering
{
    class OpenGLVertexArray : public IVertexArray
    {
    public:
        OpenGLVertexArray();
        ~OpenGLVertexArray() override;
        void Bind() const override;
        void Unbind() const override;
        void SetLayout(const VertexLayout& layout, const IVertexBuffer& vbo) override;

    private:
        static uint32 TranslateDataType(EVertexDataType type);
    private:
        uint32 id_;
    };
}