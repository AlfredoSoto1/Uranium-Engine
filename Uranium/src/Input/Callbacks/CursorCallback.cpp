#include <GLFW/glfw3.h>

#include "EventCallback.h"
#include "CursorCallback.h"
#include "Graphics/UI/Cursor.h"
#include "Graphics/Display/Window.h"
#include "Core/Application/ApplicationProgram.h"

using namespace Uranium::Input::Callbacks;
using namespace Uranium::Core::Application;

using namespace Uranium::Graphics::UI;
using namespace Uranium::Graphics::Display;

CursorCallback::CursorCallback(Window* window) :
	EventCallback(window)
{
	// initiate callbacks
	initCallbacks();
}

CursorCallback::~CursorCallback() {
	// free callbacks
	glfwSetDropCallback(*EventCallback::getWindow(), nullptr);
	glfwSetCursorEnterCallback(*EventCallback::getWindow(), nullptr);
}

void CursorCallback::initCallbacks() {
	auto dropCallback = [](GLFWwindow* window, int pathCount, const char** paths) {
		// obtain Application-program reference via glfw user pointer
		ApplicationProgram* program = static_cast<ApplicationProgram*>(glfwGetWindowUserPointer(window));
		if (program == nullptr)
			return;
	};

	auto enterCallback = [](GLFWwindow* window, int isInside) {
		// obtain Application-program reference via glfw user pointer
		ApplicationProgram* program = static_cast<ApplicationProgram*>(glfwGetWindowUserPointer(window));
		if (program == nullptr)
			return;

		// update is inside window flag as active
		program->getCursor()->isActive = isInside > 0 ? true : false;
	};

	// initialize callbacks
	glfwSetDropCallback(*EventCallback::getWindow(), dropCallback);
	glfwSetCursorEnterCallback(*EventCallback::getWindow(), enterCallback);
}

void CursorCallback::updateCallbackEvent() {

}
