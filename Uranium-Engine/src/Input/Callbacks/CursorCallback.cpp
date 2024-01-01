#include <GL/glfw3.h>

#include "CursorCallback.h"
#include "Platform/Display/Window.h"

namespace Uranium::Input::Callbacks {

	CursorCallback::CursorCallback(Window* window) noexcept {
		glfwSetDropCallback(*window,        CursorCallback::dropEvent);
		glfwSetCursorEnterCallback(*window, CursorCallback::enteredEvent);
	}

	void CursorCallback::dropEvent(GLFWwindow* window, int pathCount, const char** paths) {
		//// obtain Application-program reference via glfw user pointer
		//ApplicationProgram* program = static_cast<ApplicationProgram*>(glfwGetWindowUserPointer(window));
		//if (program == nullptr)
		//	return;
	}

	void CursorCallback::enteredEvent(GLFWwindow* window, int isInside) {
		//// obtain Application-program reference via glfw user pointer
		//ApplicationProgram* program = static_cast<ApplicationProgram*>(glfwGetWindowUserPointer(window));
		//if (program == nullptr)
		//	return;

		//// update is inside window flag as active
		//program->getCursor()->isActive = isInside > 0 ? true : false;
	}
}