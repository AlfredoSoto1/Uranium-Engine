#include <GL/glfw3.h>

#include <memory>
#include "KeyboardCallback.h"

#include "Core/Application.h"
#include "Core/Engine/BaseEngine.h"
#include "Platform/Display/Window.h"

namespace Uranium::Input::Callbacks {

	using namespace Core;
	using namespace Engine;
	using namespace Platform::Display;

	KeyboardCallback::KeyboardCallback() noexcept :
		keys(nullptr),
		toggled(false),
		released(false)
	{
		// create and initialize key buffer
		keys = new bool[GLFW_KEY_LAST];
		for (int i = 0; i < GLFW_KEY_LAST; i++)
			keys[i] = false;

		//// Obtain the window reference from the application's engine
		//std::shared_ptr<Window> window = Application::instance().getBaseEngine().getWindow();

		//glfwSetKeyCallback(*window,  KeyboardCallback::keyEvent);
		//glfwSetCharCallback(*window, KeyboardCallback::charEvent);
	}

	KeyboardCallback::~KeyboardCallback() {
		// delete the key buffer
		delete[] keys;

		// Obtain the window reference from the application's engine
		//std::shared_ptr<Window> window = Application::instance().getBaseEngine().getWindow();

		//glfwSetKeyCallback(*window,  nullptr);
		//glfwSetCharCallback(*window, nullptr);
	}

	void KeyboardCallback::keyEvent(GLFWwindow* window, int key, int scancode, int action, int mods) {
		BaseEngine& engine = Application::instance().getBaseEngine();
		//// obtain Application-program reference via glfw user pointer
		//ApplicationProgram* program = static_cast<ApplicationProgram*>(glfwGetWindowUserPointer(window));
		//if (program == nullptr)
		//	return;

		//// update key buffer
		//program->getKeyboardCallback()->keys[key] = action != GLFW_RELEASE;
	}

	void KeyboardCallback::charEvent(GLFWwindow* window, unsigned int codePoint) {
		BaseEngine& engine = Application::instance().getBaseEngine();
		// TODO
	}

	bool KeyboardCallback::isKeyDown(int key) {
		return keys[key] ? true : false;
	}

	bool KeyboardCallback::isKeyToggled(int key) {
		if (isKeyDown(key)) {
			if (!toggled) {
				toggled = true;
				return true;
			}
			else {
				return false;
			}
		}
		else {
			toggled = false;
			return false;
		}
	}

	bool KeyboardCallback::isKeyReleased(int key) {
		if (!isKeyDown(key)) {
			if (released) {
				released = false;
				return true;
			}
			return false;
		}
		else {
			released = true;
			return false;
		}
	}
}