#include <GLFW/glfw3.h>

#include "WindowCallback.h"
#include "Graphics/Display/Window.h"

using namespace Uranium::Input;
using namespace Uranium::Graphics::Display;

WindowCallback::WindowCallback(Window* window) :
	window(window),
	has_Resized(false)
{
	auto positionCallback = [](GLFWwindow* winPtr, int xpos, int ypos) {
		//Window& window = Application::get().getWindow();
		//window.getSettings().changePosition(xpos, ypos);
		//if (window.listener != nullptr)
		//	window.listener->windowMoved(xpos, ypos);
	};

	auto sizeCallback = [](GLFWwindow* winPtr, int width, int height) {
		//Window& window = Application::get().getWindow();
		//window.getSettings().changeSize(width, height);
		//if (window.listener != nullptr)
		//	window.listener->windowSize(width, height);
	};

	auto closeCallback = [](GLFWwindow* winPtr) {
		//Window& window = Application::get().getWindow();
		//if (window.listener != nullptr)
		//	window.listener->windowClosed();
	};

	auto focusCallback = [](GLFWwindow* winPtr, int isFocused) {
		//Window& window = Application::get().getWindow();
		//if (window.listener != nullptr)
		//	window.listener->windowFocused(isFocused > 0 ? true : false);
	};

	auto iconifyCallback = [](GLFWwindow* winPtr, int isIconified) {
		//Window& window = Application::get().getWindow();
		//if (window.listener != nullptr)
		//	window.listener->windowIconified(isIconified > 0 ? true : false);
	};

	auto maximizeCallback = [](GLFWwindow* winPtr, int isMaximized) {
		//Window& window = Application::get().getWindow();
		//if (window.listener != nullptr)
		//	window.listener->windowMaximized(isMaximized > 0 ? true : false);
	};

	auto refreshCallback = [](GLFWwindow* winPtr) {
		//Window& window = Application::get().getWindow();
		//if (window.listener != nullptr)
		//	window.listener->windowRefresh();
	};

	auto frameBufferSizeCallback = [](GLFWwindow* winPtr, int width, int height) {
		//Window& window = Application::get().getWindow();
		//if (window.listener != nullptr)
		//	window.listener->windowFrameBufferSize(width, height);
	};

	//sets the corresponding callback to GLFW
	glfwSetWindowPosCallback(*window, positionCallback);
	glfwSetWindowSizeCallback(*window, sizeCallback);
	glfwSetWindowCloseCallback(*window, closeCallback);
	glfwSetWindowFocusCallback(*window, focusCallback);
	glfwSetWindowIconifyCallback(*window, iconifyCallback);
	glfwSetWindowRefreshCallback(*window, refreshCallback);
	glfwSetWindowMaximizeCallback(*window, maximizeCallback);
	glfwSetFramebufferSizeCallback(*window, frameBufferSizeCallback);
}

WindowCallback::~WindowCallback() {

}

bool WindowCallback::hasResized() {
	return has_Resized;
}