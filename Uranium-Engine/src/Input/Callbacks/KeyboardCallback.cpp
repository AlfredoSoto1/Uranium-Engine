#include <GLFW/glfw3.h>

#include "KeyboardCallback.h"
#include "Graphics/Display/Window.h"

namespace Uranium::Input::Callbacks {

	KeyboardCallback::KeyboardCallback(Window* window) :
		window(window),

		keys(nullptr),
		toggled(false),
		released(false)
	{
		// create and initialize key buffer
		keys = new bool[GLFW_KEY_LAST];
		for (int i = 0; i < GLFW_KEY_LAST; i++)
			keys[i] = false;

		glfwSetKeyCallback(*window,  KeyboardCallback::keyDetected);
		glfwSetCharCallback(*window, KeyboardCallback::charDetected);
	}

	KeyboardCallback::~KeyboardCallback() {
		delete[] keys;

		glfwSetKeyCallback(*window,  nullptr);
		glfwSetCharCallback(*window, nullptr);
	}

	void KeyboardCallback::keyDetected(GLFWwindow* window, int key, int scancode, int action, int mods) {
		//// obtain Application-program reference via glfw user pointer
		//ApplicationProgram* program = static_cast<ApplicationProgram*>(glfwGetWindowUserPointer(window));
		//if (program == nullptr)
		//	return;

		//// update key buffer
		//program->getKeyboardCallback()->keys[key] = action != GLFW_RELEASE;
	}

	void KeyboardCallback::charDetected(GLFWwindow* window, unsigned int codePoint) {
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