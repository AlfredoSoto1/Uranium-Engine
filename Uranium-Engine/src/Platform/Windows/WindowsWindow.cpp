#define GLFW_INCLUDE_VULKAN
#include <GLFW/glfw3.h>

#include <stdexcept>

#include "WindowsWindow.h"

namespace Uranium::Platform::Windows {

	WindowsWindow::WindowsWindow(const std::string& title, unsigned int width, unsigned int height) :
		title(title),
		width(width),
		height(height),
		frameBufferResized(false)
	{
		// glfw should be already initiated
		glfwInit();

		// Prepare hints
		glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);
		glfwWindowHint(GLFW_CENTER_CURSOR, GLFW_TRUE);

		glfwWindow = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);

        if (glfwWindow == nullptr)
            throw std::runtime_error("Failed to create GLFW window!");

		glfwSetWindowUserPointer(glfwWindow, this);

		// Create and prepare callbacks (must do in application)
		glfwSetFramebufferSizeCallback(glfwWindow, [](GLFWwindow* glfwWindow, int width, int height) {
			WindowsWindow& window = *(WindowsWindow*)glfwGetWindowUserPointer(glfwWindow);
			window.frameBufferResized = true;
		});
	}
}