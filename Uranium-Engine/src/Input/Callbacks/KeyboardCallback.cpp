#include <GL/glfw3.h>

#include "KeyboardCallback.h"
#include "Platform/Display/Window.h"

namespace Uranium::Input::Callbacks {

	KeyboardCallback::KeyboardCallback(Window* window) noexcept :
		keys(nullptr),
		keyPressedEvent(0, 0, 0),
		keyReleasedEvent(0, 0)
	{
		// create and initialize key buffer
		keys = new bool[GLFW_KEY_LAST];
		for (int i = 0; i < GLFW_KEY_LAST; i++)
			keys[i] = false;

		glfwSetKeyCallback(*window,  KeyboardCallback::key_callback);
	}

	void KeyboardCallback::key_callback(GLFWwindow* glWindow, int key, int scancode, int action, int mods) {

		Window& window = *(Window*)glfwGetWindowUserPointer(glWindow);
		//program->getKeyboardCallback()->keys[key] = action != GLFW_RELEASE;

		switch (action) {
			case GLFW_PRESS:
			{
				window.keyboardCallback->keyPressedEvent.count = 0;
				window.keyboardCallback->keyPressedEvent.keyChar = key;
				window.keyboardCallback->keyPressedEvent.scancode = scancode;
				window.callbackFunction(window.keyboardCallback->keyPressedEvent);
				break;
			}
			case GLFW_RELEASE:
			{
				window.keyboardCallback->keyReleasedEvent.keyChar = key;
				window.keyboardCallback->keyReleasedEvent.scancode = scancode;
				window.callbackFunction(window.keyboardCallback->keyReleasedEvent);
				break;
			}
			case GLFW_REPEAT:
			{
				window.keyboardCallback->keyPressedEvent.count++;
				window.keyboardCallback->keyPressedEvent.keyChar = key;
				window.keyboardCallback->keyPressedEvent.scancode = scancode;
				window.callbackFunction(window.keyboardCallback->keyPressedEvent);
				break;
			}
		}
	}

	bool KeyboardCallback::isKeyDown(int key) {
		return keys[key] ? true : false;
	}
}