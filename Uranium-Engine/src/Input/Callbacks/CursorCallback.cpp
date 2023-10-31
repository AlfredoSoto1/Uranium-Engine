#include <GLFW/glfw3.h>

#include "CursorCallback.h"
#include "Graphics/Display/Window.h"

namespace Uranium::Input::Callbacks {

	CursorCallback::CursorCallback(Window* window) :
		window(window)
	{
		glfwSetDropCallback(*window,        CursorCallback::dropDetected);
		glfwSetCursorEnterCallback(*window, CursorCallback::enteredDetected);
	}

	CursorCallback::~CursorCallback() {
		glfwSetDropCallback(*window,        nullptr);
		glfwSetCursorEnterCallback(*window, nullptr);
	}

	void CursorCallback::dropDetected(GLFWwindow* window, int pathCount, const char** paths) {
		//// obtain Application-program reference via glfw user pointer
		//ApplicationProgram* program = static_cast<ApplicationProgram*>(glfwGetWindowUserPointer(window));
		//if (program == nullptr)
		//	return;
	}

	void CursorCallback::enteredDetected(GLFWwindow* window, int isInside) {
		//// obtain Application-program reference via glfw user pointer
		//ApplicationProgram* program = static_cast<ApplicationProgram*>(glfwGetWindowUserPointer(window));
		//if (program == nullptr)
		//	return;

		//// update is inside window flag as active
		//program->getCursor()->isActive = isInside > 0 ? true : false;
	}
}