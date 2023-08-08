#include <GLFW/glfw3.h>

#include <memory>

#include "WindowCallback.h"
#include "Uranium/Graphics/Display/Window.h"

namespace Uranium::Callbacks {

	WindowCallback::WindowCallback(std::shared_ptr<Window> window) :
		window(window)
	{
		glfwSetWindowPosCallback(*window,       WindowCallback::positionChange);
		glfwSetWindowSizeCallback(*window,      WindowCallback::sizeChange);
		glfwSetWindowCloseCallback(*window,     WindowCallback::windowClose);
		glfwSetWindowFocusCallback(*window,     WindowCallback::onFocus);
		glfwSetWindowIconifyCallback(*window,   WindowCallback::minimize);
		glfwSetWindowRefreshCallback(*window,   WindowCallback::canvasRefresh);
		glfwSetWindowMaximizeCallback(*window,  WindowCallback::maximize);
		glfwSetFramebufferSizeCallback(*window, WindowCallback::frameBufferSize);
	}

	WindowCallback::~WindowCallback() {
		glfwSetWindowPosCallback(*window,       nullptr);
		glfwSetWindowSizeCallback(*window,      nullptr);
		glfwSetWindowCloseCallback(*window,     nullptr);
		glfwSetWindowFocusCallback(*window,     nullptr);
		glfwSetWindowIconifyCallback(*window,   nullptr);
		glfwSetWindowRefreshCallback(*window,   nullptr);
		glfwSetWindowMaximizeCallback(*window,  nullptr);
		glfwSetFramebufferSizeCallback(*window, nullptr);
	}

	void WindowCallback::windowClose(GLFWwindow* glWindow) {
		Window& window = *static_cast<Window*>(glfwGetWindowUserPointer(glWindow));
	}

	void WindowCallback::sizeChange(GLFWwindow* glWindow, int width, int height) {
		Window& window = *static_cast<Window*>(glfwGetWindowUserPointer(glWindow));
	}

	void WindowCallback::positionChange(GLFWwindow* glWindow, int xpos, int ypos) {
		Window& window = *static_cast<Window*>(glfwGetWindowUserPointer(glWindow));
	}

	void WindowCallback::onFocus(GLFWwindow* glWindow, int isFocused) {
		Window& window = *static_cast<Window*>(glfwGetWindowUserPointer(glWindow));
	}

	void WindowCallback::minimize(GLFWwindow* glWindow, int isMinimized) {
		Window& window = *static_cast<Window*>(glfwGetWindowUserPointer(glWindow));
	}

	void WindowCallback::maximize(GLFWwindow* glWindow, int isMaximized) {
		Window& window = *static_cast<Window*>(glfwGetWindowUserPointer(glWindow));
	}

	void WindowCallback::canvasRefresh(GLFWwindow* glWindow) {
		Window& window = *static_cast<Window*>(glfwGetWindowUserPointer(glWindow));
	}

	void WindowCallback::frameBufferSize(GLFWwindow* glWindow, int width, int height) {
		Window& window = *static_cast<Window*>(glfwGetWindowUserPointer(glWindow));
	}
}