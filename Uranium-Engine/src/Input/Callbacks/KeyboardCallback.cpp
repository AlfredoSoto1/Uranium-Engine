#include <GL/glfw3.h>

#include "KeyboardCallback.h"
#include "Platform/Display/Window.h"

namespace Uranium::Input::Callbacks {

	KeyboardCallback::KeyboardCallback(Platform::Display::Window* window) noexcept :
		keys(nullptr),
		toggled(false),
		released(false)
	{
		// create and initialize key buffer
		keys = new bool[GLFW_KEY_LAST];
		for (int i = 0; i < GLFW_KEY_LAST; i++)
			keys[i] = false;

		glfwSetKeyCallback(*window,  KeyboardCallback::keyEvent);
		glfwSetCharCallback(*window, KeyboardCallback::charEvent);
	}

	void KeyboardCallback::keyEvent(GLFWwindow* window, int key, int scancode, int action, int mods) {
		//// obtain Application-program reference via glfw user pointer
		//ApplicationProgram* program = static_cast<ApplicationProgram*>(glfwGetWindowUserPointer(window));
		//if (program == nullptr)
		//	return;

		//// update key buffer
		//program->getKeyboardCallback()->keys[key] = action != GLFW_RELEASE;
	}

	void KeyboardCallback::charEvent(GLFWwindow* window, unsigned int codePoint) {
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