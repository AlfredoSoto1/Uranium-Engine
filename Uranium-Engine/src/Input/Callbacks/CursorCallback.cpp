#include <GL/glfw3.h>

#include <memory>
#include "CursorCallback.h"

#include "Core/Application.h"
#include "Core/Engine/BaseEngine.h"
#include "Platform/Display/Window.h"

namespace Uranium::Input::Callbacks {

	using namespace Core;
	using namespace Engine;
	using namespace Platform::Display;

	CursorCallback::CursorCallback() noexcept {
		// Obtain the window reference from the application's engine
		std::shared_ptr<Window> window = Application::instance().getBaseEngine().getWindow();

		glfwSetDropCallback(*window,        CursorCallback::dropEvent);
		glfwSetCursorEnterCallback(*window, CursorCallback::enteredEvent);
	}

	CursorCallback::~CursorCallback() {
		// Obtain the window reference from the application's engine
		std::shared_ptr<Window> window = Application::instance().getBaseEngine().getWindow();

		glfwSetDropCallback(*window,        nullptr);
		glfwSetCursorEnterCallback(*window, nullptr);
	}

	void CursorCallback::dropEvent(GLFWwindow* window, int pathCount, const char** paths) {
		BaseEngine& engine = Application::instance().getBaseEngine();
		//// obtain Application-program reference via glfw user pointer
		//ApplicationProgram* program = static_cast<ApplicationProgram*>(glfwGetWindowUserPointer(window));
		//if (program == nullptr)
		//	return;
	}

	void CursorCallback::enteredEvent(GLFWwindow* window, int isInside) {
		BaseEngine& engine = Application::instance().getBaseEngine();
		//// obtain Application-program reference via glfw user pointer
		//ApplicationProgram* program = static_cast<ApplicationProgram*>(glfwGetWindowUserPointer(window));
		//if (program == nullptr)
		//	return;

		//// update is inside window flag as active
		//program->getCursor()->isActive = isInside > 0 ? true : false;
	}
}