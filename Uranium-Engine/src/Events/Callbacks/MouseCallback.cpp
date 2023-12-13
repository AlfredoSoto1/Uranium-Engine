#include <GL/glfw3.h>

#include <memory>
#include "MouseCallback.h"

#include "Core/BaseEngine.h"
#include "Services/Application.h"
#include "Graphics/Viewport/Window.h"

using namespace Uranium::Core;
using namespace Uranium::Services;
using namespace Uranium::Graphics::Display;
using namespace Uranium::Graphics::Viewport;

namespace Uranium::Events::Callbacks {

	MouseCallback::MouseCallback() noexcept:
		mouseButtons(nullptr)
	{
		// Obtain the window reference from the application's engine
		std::shared_ptr<Window> window = Application::instance().getBaseEngine().getWindow();

		// create bool array containing
		// mouse button activation flag
		// for each button when being interacted with
		mouseButtons = new bool[GLFW_MOUSE_BUTTON_LAST];

		glfwSetScrollCallback(*window,      MouseCallback::scrollEvent);
		glfwSetCursorPosCallback(*window,   MouseCallback::movedEvent);
		glfwSetMouseButtonCallback(*window, MouseCallback::clickEvent);
	}

	MouseCallback::~MouseCallback() {
		// Obtain the window reference from the application's engine
		std::shared_ptr<Window> window = Application::instance().getBaseEngine().getWindow();

		delete[] mouseButtons;

		glfwSetScrollCallback(*window,      nullptr);
		glfwSetCursorPosCallback(*window,   nullptr);
		glfwSetMouseButtonCallback(*window, nullptr);
	}

	void MouseCallback::clickEvent(GLFWwindow* window, int button, int action, int mods) {
		BaseEngine& engine = Application::instance().getBaseEngine();

		//// obtain Application-program reference via glfw user pointer
		//ApplicationProgram* program = static_cast<ApplicationProgram*>(glfwGetWindowUserPointer(window));
		//if (program == nullptr)
		//	return;

		//// update mouse button actions
		//program->getMouseCallback()->mouseButtons[button] = action != GLFW_RELEASE;
	}

	void MouseCallback::scrollEvent(GLFWwindow* window, double xOffset, double yOffset) {
		BaseEngine& engine = Application::instance().getBaseEngine();
		//// obtain Application-program reference via glfw user pointer
		//ApplicationProgram* program = static_cast<ApplicationProgram*>(glfwGetWindowUserPointer(window));
		//if (program == nullptr)
		//	return;
	}

	void MouseCallback::movedEvent(GLFWwindow* window, double xpos, double ypos) {
		BaseEngine& engine = Application::instance().getBaseEngine();
		//// obtain Application-program reference via glfw user pointer
		//ApplicationProgram* program = static_cast<ApplicationProgram*>(glfwGetWindowUserPointer(window));
		//if (program == nullptr)
		//	return;

		//// save window size for later use
		//unsigned int width = program->getWindow()->getProperties().getWidth();
		//unsigned int height = program->getWindow()->getProperties().getHeight();

		//// change cursor position
		//program->getCursor()->xPosition = xpos;
		//program->getCursor()->yPosition = ypos;

		//// change cursor position in normal coordinates
		//program->getCursor()->setNormPosition((xpos * 2.0) / width - 1.0, -(ypos * 2.0) / height + 1.0);
	}

	bool MouseCallback::isButtonDown(int button) {
		if (button < 0)
			return false;
		return mouseButtons[button] ? true : false;
	}
}
