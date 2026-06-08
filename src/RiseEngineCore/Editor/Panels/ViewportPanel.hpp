#pragma once
#include "IPanel.hpp"
#include <glm/glm.hpp>

namespace RiseEngine::Rendering
{
    class IFramebuffer;
}

namespace RiseEngine::Editor
{
    class ViewportPanel : public IPanel
    {
    public:
        explicit ViewportPanel(RiseEngine::Rendering::IFramebuffer* framebuffer);
        ~ViewportPanel() override = default;

        void Render() const override;
    
    public:
        // Returns the current
        glm::vec2 GetViewportSize() const { return viewportSize_; }
        bool      WasResized()      const { return bWasResized_; }

    private:
        RiseEngine::Rendering::IFramebuffer* framebuffer_ = nullptr; // Not owning.
        mutable glm::vec2 viewportSize_ = { 800.0f, 600.f };
        mutable bool bWasResized_ = false;
    };
}