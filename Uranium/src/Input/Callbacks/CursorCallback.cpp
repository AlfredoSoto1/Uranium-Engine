#include <GLFW/glfw3.h>

#include "EventCallback.h"
#include "CursorCallback.h"
#include "Graphics/Display/Window.h"

using namespace Uranium::Input::Callbacks;
using namespace Uranium::Graphics::Display;

CursorCallback::CursorCallback(Window* window) :
	EventCallback(window)
{
	// initiate callbacks
	initCallbacks();
}

CursorCallback::~CursorCallback() {

}

void CursorCallback::initCallbacks() {
	auto dropCallback = [](GLFWwindow* winPtr, int pathCount, const char** paths) {
		//Mouse& mouse = Application::get().getMouse();
	};

	auto enterCallback = [](GLFWwindow* winPtr, int isInside) {
		//Mouse& mouse = Application::get().getMouse();
		//mouse.getCursor().isActive = isInside > 0 ? true : false;
	};

	glfwSetDropCallback(*EventCallback::getWindow(), dropCallback);
	glfwSetCursorEnterCallback(*EventCallback::getWindow(), enterCallback);
}

void CursorCallback::updateCallbackEvent() {

}
