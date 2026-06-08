#include "ViewportPanel.hpp"
#include <Rendering/include/Primitives/ITexture2D.hpp>
#include <Rendering/include/Primitives/IFramebuffer.hpp>
#include <vendor/imgui/imgui.h>

using ViewportPanel = RiseEngine::Editor::ViewportPanel;

ViewportPanel::ViewportPanel(RiseEngine::Rendering::IFramebuffer* framebuffer)
	: IPanel("Viewport Panel"), framebuffer_(framebuffer)
{
}


void ViewportPanel::Render() const
{
	ImGuiViewport* viewport = ImGui::GetMainViewport();
	ImGui::SetNextWindowPos(viewport->WorkPos);
	ImGui::SetNextWindowSize(viewport->WorkSize);

	ImGuiWindowFlags flags =
//		ImGuiWindowFlags_NoTitleBar |
		ImGuiWindowFlags_NoCollapse |
		ImGuiWindowFlags_NoMove |
		ImGuiWindowFlags_NoResize |
//		ImGuiWindowFlags_NoBringToFrontOnFocus | This flag causes main scene viewport to turn gray-ish.
		ImGuiWindowFlags_NoNav |
		ImGuiWindowFlags_NoDocking // Viewport cannot move away from the dockspace.
		;

	ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
	ImGui::Begin(title_.c_str(), nullptr, flags);
	ImGui::PopStyleVar();

	// Detect if panel size changed.
	ImVec2 panelSize = ImGui::GetContentRegionAvail();
	bWasResized_ = (panelSize.x != viewportSize_.x || panelSize.y != viewportSize_.y);
	viewportSize_ = { panelSize.x, panelSize.y };

	// Display framebuffer texture as image.
	uint64 textureID = framebuffer_->GetColorAttachment()->GetId();
	ImGui::Image(
		reinterpret_cast<void*>(textureID),
		panelSize,
		ImVec2(0, 1),// UV flip vertical — OpenGL has inverted Y.
		ImVec2(1, 0)
	);

	ImGui::End();
}
