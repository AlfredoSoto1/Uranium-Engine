#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include <stdexcept>

#include "WindowsWindow.h"

namespace Uranium::Platform::Windows {

	WindowsWindow::WindowsWindow(
		const std::string& title = "Uranium-Window", // 
		uint32_t width  = MIN_WIDTH,			     // default values are set if no arguments are provided
		uint32_t height = MIN_HEIGHT				 // 
	):		
		Window(title, width, height)
	{
	}

	WindowsWindow::~WindowsWindow() noexcept {

	}

	void WindowsWindow::setVSync(bool enabled) {

	}

	void WindowsWindow::setVisible(bool visible) {

	}

	void WindowsWindow::setResizable(bool resizable) {

	}

	void WindowsWindow::setDecorated(bool decorated) {

	}

	void WindowsWindow::setAlwaysOnTop(bool alwaysOnTop) {

	}

	void WindowsWindow::close() {

	}

	void WindowsWindow::focus() {

	}

	void WindowsWindow::requestAttention() {

	}

	void WindowsWindow::restore() {

	}

	void WindowsWindow::maximize() {

	}

	void WindowsWindow::minimize() {

	}

	void WindowsWindow::center(MonitorRef monitor) {

	}

	void WindowsWindow::setFullscreen(MonitorRef monitor) {

	}
}