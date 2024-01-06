#pragma once

#include <string>

namespace Uranium::Platform::Windows {

	class WindowsWindow final {
	public:
		explicit WindowsWindow(const std::string& title, unsigned int width, unsigned int height);

	private:
		static constexpr unsigned int MIN_WIDTH = 320;
		static constexpr unsigned int MIN_HEIGHT = 180;
		
		GLFWwindow* glfwWindow;

		unsigned int width;
		unsigned int height;

		std::string title;

		bool frameBufferResized;
	};
}