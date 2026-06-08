#pragma once
#include <string>

namespace RiseEngine::Editor
{
	// Base interface for all editor panels.
	class IPanel
	{
	public:
		explicit IPanel(const std::string& title) : title_(title) {}
		virtual ~IPanel() = default;

		virtual void Render() const = 0;

	public:
		inline const std::string& GetTitle() const { return title_; }
		inline bool IsVisible() const { return bVisible_; }
		inline void SetVisible(const bool bVisible) { bVisible_ = bVisible; }

	protected:
		std::string title_;
		bool bVisible_ = true;
	};
}