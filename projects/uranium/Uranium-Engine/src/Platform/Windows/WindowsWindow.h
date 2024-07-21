#pragma once

#include <string>

#include "Core/CoreMacros.h"
#include "Platform/Interface/Window.h"

namespace Uranium::Platform::Windows {

	URANIUM_API class WindowsWindow final :
		UR_EXTENDS Interface::Window
	{
	public:
		explicit WindowsWindow(const std::string& title, uint32_t width, uint32_t height);
		
		~WindowsWindow() noexcept;

	public:
		void setVSync(bool enabled);

	public:
		void setVisible(bool visible) override;
		void setResizable(bool resizable) override;
		void setDecorated(bool decorated) override;
		void setAlwaysOnTop(bool alwaysOnTop) override;

	public:
		void close() override;
		void focus() override;
		void requestAttention() override;

	public:
		void restore() override;
		void maximize() override;
		void minimize() override;

	public:
		void center(MonitorRef monitor) override;
		void setFullscreen(MonitorRef monitor) override;
	};
}