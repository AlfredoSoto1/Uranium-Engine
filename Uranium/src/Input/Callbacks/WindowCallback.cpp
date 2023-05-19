#include <GLFW/glfw3.h>

#include "WindowCallback.h"
#include "Graphics/Display/Window.h"
#include "Graphics/Display/WindowProps.h"
#include "Core/Application/ApplicationProgram.h"

using namespace Uranium::Input::Callbacks;
using namespace Uranium::Graphics::Display;
using namespace Uranium::Core::Application;

WindowCallback::WindowCallback(Window* window) :
	EventCallback(window),
	has_Resized(false)
{
	// Initiate Callback
	initCallbacks();
}

WindowCallback::~WindowCallback() {

	// free callbacks
	glfwSetWindowPosCallback(*EventCallback::getWindow(), nullptr);
	glfwSetWindowSizeCallback(*EventCallback::getWindow(), nullptr);
	glfwSetWindowCloseCallback(*EventCallback::getWindow(), nullptr);
	glfwSetWindowFocusCallback(*EventCallback::getWindow(), nullptr);
	glfwSetWindowIconifyCallback(*EventCallback::getWindow(), nullptr);
	glfwSetWindowRefreshCallback(*EventCallback::getWindow(), nullptr);
	glfwSetWindowMaximizeCallback(*EventCallback::getWindow(), nullptr);
	glfwSetFramebufferSizeCallback(*EventCallback::getWindow(), nullptr);
}

void WindowCallback::initCallbacks() { 

	auto positionCallback = [](GLFWwindow* window, int xpos, int ypos) {

		// obtain Application-program reference via glfw user pointer
		ApplicationProgram* program = static_cast<ApplicationProgram*>(glfwGetWindowUserPointer(window));
		if (program == nullptr)
			return;

		// update window props for
		// xPosition and yPosition
		program->getWindow()->getProperties().xPosition = xpos;
		program->getWindow()->getProperties().yPosition = ypos;
	};

	auto sizeCallback = [](GLFWwindow* window, int width, int height) {

		// obtain Application-program reference via glfw user pointer
		ApplicationProgram* program = static_cast<ApplicationProgram*>(glfwGetWindowUserPointer(window));
		if (program == nullptr)
			return;

		// update resize flag
		program->getWindowCallback()->has_Resized = true;

		// update window props for
		// width and height
		program->getWindow()->getProperties().width = width;
		program->getWindow()->getProperties().height = height;

	};

	auto closeCallback = [](GLFWwindow* window) {
		//Window& window = Application::get().getWindow();
		//if (window.listener != nullptr)
		//	window.listener->windowClosed();
	};

	auto focusCallback = [](GLFWwindow* window, int isFocused) {
		//Window& window = Application::get().getWindow();
		//if (window.listener != nullptr)
		//	window.listener->windowFocused(isFocused > 0 ? true : false);
	};

	auto iconifyCallback = [](GLFWwindow* window, int isIconified) {
		//Window& window = Application::get().getWindow();
		//if (window.listener != nullptr)
		//	window.listener->windowIconified(isIconified > 0 ? true : false);
	};

	auto maximizeCallback = [](GLFWwindow* window, int isMaximized) {
		//Window& window = Application::get().getWindow();
		//if (window.listener != nullptr)
		//	window.listener->windowMaximized(isMaximized > 0 ? true : false);
	};

	auto refreshCallback = [](GLFWwindow* window) {
		//Window& window = Application::get().getWindow();
		//if (window.listener != nullptr)
		//	window.listener->windowRefresh();
	};

	auto frameBufferSizeCallback = [](GLFWwindow* window, int width, int height) {
		//Window& window = Application::get().getWindow();
		//if (window.listener != nullptr)
		//	window.listener->windowFrameBufferSize(width, height);
	};

	// sets the corresponding callback to GLFW
	glfwSetWindowPosCallback(*EventCallback::getWindow(), positionCallback);
	glfwSetWindowSizeCallback(*EventCallback::getWindow(), sizeCallback);
	glfwSetWindowCloseCallback(*EventCallback::getWindow(), closeCallback);
	glfwSetWindowFocusCallback(*EventCallback::getWindow(), focusCallback);
	glfwSetWindowIconifyCallback(*EventCallback::getWindow(), iconifyCallback);
	glfwSetWindowRefreshCallback(*EventCallback::getWindow(), refreshCallback);
	glfwSetWindowMaximizeCallback(*EventCallback::getWindow(), maximizeCallback);
	glfwSetFramebufferSizeCallback(*EventCallback::getWindow(), frameBufferSizeCallback);
}

void WindowCallback::updateCallbackEvent() { 
	
	// update resize flag
	has_Resized = false;
}

bool WindowCallback::hasResized() {
	return has_Resized;
}