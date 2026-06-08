#include "EditorContext.hpp"
#include <vendor/imgui/imgui.h>
#include <vendor/imgui/imgui_internal.h>

using EditorContext = RiseEngine::Editor::EditorContext;

void EditorContext::Init(GLFWwindow* window)
{
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();

	ImGuiIO& io = ImGui::GetIO();
	io.IniFilename = nullptr; // Do not save layout.

	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;  // Enable Keyboard Controls.
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;   // Enable Gamepad Controls.
	io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;      // Enable Docking.

	ImGui::StyleColorsDark();

	ImGuiStyle& style = ImGui::GetStyle();
	if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
	{
		style.WindowRounding = 0.f;
		style.Colors[ImGuiCol_WindowBg].w = 1.f; // Ensure opaque background for viewports to avoid visual artifacts when dragging windows outside the main viewport.
	}

	ImGui_ImplGlfw_InitForOpenGL(window, true);
}

void EditorContext::Shutdown()
{
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
}

void EditorContext::RenderPanels() const
{
	BeginDockspace();
	for (const auto& panel : panels_)
	{
		if(panel->IsVisible())
			panel->Render();
	}
	EndDockspace();
}

void EditorContext::BeginDockspace() const
{
	ImGuiWindowFlags flags =
		ImGuiWindowFlags_NoDocking |
		ImGuiWindowFlags_NoTitleBar |
		ImGuiWindowFlags_NoCollapse |
		ImGuiWindowFlags_NoResize |
		ImGuiWindowFlags_NoMove |
		ImGuiWindowFlags_NoBringToFrontOnFocus |
		ImGuiWindowFlags_NoNavFocus |
		ImGuiWindowFlags_MenuBar;
	
	ImGuiViewport* viewport = ImGui::GetMainViewport();
	ImGui::SetNextWindowPos(viewport->Pos);
	ImGui::SetNextWindowSize(viewport->Size);
	ImGui::SetNextWindowViewport(viewport->ID);

	ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.f);
	ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.f);
	ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.f, 0.f));

	ImGui::Begin("##Dockspace", nullptr, flags);
	ImGui::PopStyleVar(3);

	ImGuiID dockspaceID = ImGui::GetID("MainDockspace");
	ImGui::DockSpace(dockspaceID, ImVec2(0.f,0.f), ImGuiDockNodeFlags_PassthruCentralNode | ImGuiDockNodeFlags_NoTabBar);
	/*
	static bool firstTime = true;
	if (firstTime)
	{
		firstTime = false;

//		if (!ImGui::DockBuilderGetNode(dockspaceID)) // Construct node.
//		{
			ImGui::DockBuilderRemoveNode(dockspaceID);
			ImGui::DockBuilderAddNode(dockspaceID, ImGuiDockNodeFlags_DockSpace);
			ImGui::DockBuilderSetNodeSize(dockspaceID, ImGui::GetMainViewport()->Size);
			ImGui::DockBuilderDockWindow("Viewport Panel", dockspaceID); // window_name should be the same as ViewportPanel title_
			// Fixed viewport inside the window.
			ImGui::DockBuilderGetNode(dockspaceID)->LocalFlags |=
				ImGuiDockNodeFlags_NoTabBar |
				ImGuiDockNodeFlags_NoResize |
				ImGuiDockNodeFlags_NoDockingOverMe;
			ImGui::DockBuilderFinish(dockspaceID);
//		}
	}
	*/
//	ImGui::DockSpace(dockspaceID);
}

void EditorContext::EndDockspace() const
{
	ImGui::End();
}

bool EditorContext::WantCaptureMouse() const
{
	return ImGui::GetIO().WantCaptureMouse;
}

bool EditorContext::WantCaptureKeyboard() const
{
	return ImGui::GetIO().WantCaptureKeyboard;
}
