#include <GLFW/glfw3.h>

#include <memory>

#include "WindowCallback.h"
#include "Uranium/Listeners/WindowListener.h"

#include "Uranium/Graphics/Display/Window.h"

namespace Uranium::Callbacks {

	// 
	// Create all the corresponding callbacks
	// related to window events
	//
	WindowCallback::WindowCallback(Window* window) :
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

	// 
	// Free all the window callbacks created
	//
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

		if (window.getWindowListener() == nullptr)
			return;

		window.getWindowListener()->onClose();
	}

	void WindowCallback::sizeChange(GLFWwindow* glWindow, int width, int height) {
		Window& window = *static_cast<Window*>(glfwGetWindowUserPointer(glWindow));

		// Update resized flag to true
		window.getModes().resized = true;

		if (window.getWindowListener() == nullptr)
			return;

		window.getWindowListener()->onResize(width, height);
	}

	void WindowCallback::positionChange(GLFWwindow* glWindow, int xpos, int ypos) {
		Window& window = *static_cast<Window*>(glfwGetWindowUserPointer(glWindow));

		if (window.getWindowListener() == nullptr)
			return;

		window.getWindowListener()->onMoved(xpos, ypos);
	}

	void WindowCallback::onFocus(GLFWwindow* glWindow, int isFocused) {
		Window& window = *static_cast<Window*>(glfwGetWindowUserPointer(glWindow));

		if (window.getWindowListener() == nullptr)
			return;

		if(isFocused)
			window.getWindowListener()->onFocus();
		else
			window.getWindowListener()->offFocus();
	}

	void WindowCallback::minimize(GLFWwindow* glWindow, int isMinimized) {
		Window& window = *static_cast<Window*>(glfwGetWindowUserPointer(glWindow));

		if (window.getWindowListener() == nullptr)
			return;

		if (isMinimized)
			window.getWindowListener()->onMinimized();
	}

	void WindowCallback::maximize(GLFWwindow* glWindow, int isMaximized) {
		Window& window = *static_cast<Window*>(glfwGetWindowUserPointer(glWindow));
		
		if (window.getWindowListener() == nullptr)
			return;

		if (isMaximized)
			window.getWindowListener()->onMaximized();
	}

	void WindowCallback::canvasRefresh(GLFWwindow* glWindow) {
		Window& window = *static_cast<Window*>(glfwGetWindowUserPointer(glWindow));

		if (window.getWindowListener() == nullptr)
			return;

		window.getWindowListener()->onCanvasRefresh();
	}

	void WindowCallback::frameBufferSize(GLFWwindow* glWindow, int width, int height) {
		Window& window = *static_cast<Window*>(glfwGetWindowUserPointer(glWindow));

		if (window.getWindowListener() == nullptr)
			return;

		window.getWindowListener()->onFramebufferResize(width, height);
	}
}