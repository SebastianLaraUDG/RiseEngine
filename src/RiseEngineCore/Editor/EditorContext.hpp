#pragma once
#include "Panels/IPanel.hpp"
#include "EditorSelection.hpp"

struct GLFWwindow;

namespace RiseEngine::Editor
{
    /*
    * Manages the entire editor lifecycle.
    * - Owns the ImGui context
    * - Owns all panels
    * - Holds the shared EditorSelection state
    *
    * Usage:
    *   Init()       — once after window and RHI are created
    *   BeginFrame() — start of each frame
    *   EndFrame()   — end of each frame, after all panel OnRender() calls
    *   Shutdown()   — once before destroying window and RHI
	*
	* Note this engine uses glfw as default.
    */
	class EditorContext
	{
    public:
		EditorContext() = default;
		~EditorContext() = default;

		void Init(GLFWwindow* window);
        void Shutdown();

		void RenderPanels() const;

		template<typename T, typename... Args>
		T* AddPanel(Args&&... args)
		{
            static_assert(std::is_base_of_v<IPanel, T>, "T must derive from IPanel");
			auto panel = std::make_unique<T>(std::forward<Args>(args)...);
			T* ptr = panel.get();
			panels_.emplace_back(std::move(panel));
            return ptr;
		}

	private:
		void BeginDockspace() const;
		void EndDockspace() const;

	public:
		inline EditorSelection& GetSelection() { return selection_; }
		bool WantCaptureMouse() const;
		bool WantCaptureKeyboard() const;

    private:
		std::vector<std::unique_ptr<IPanel>> panels_;
        EditorSelection selection_;
	};
}