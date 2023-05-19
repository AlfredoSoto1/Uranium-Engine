#include <GLFW/glfw3.h>

#include "KeyboardCallback.h"
#include "Graphics/Display/Window.h"

using namespace Uranium::Input::Callbacks;
using namespace Uranium::Graphics::Display;

KeyboardCallback::KeyboardCallback(Window* window) :
	EventCallback(window),
	toggled(false),
	released(false)
{
	// initiate callbacks
	initCallbacks();
}

KeyboardCallback::~KeyboardCallback() {
	delete[] keys;
}

void KeyboardCallback::initCallbacks() {
	auto keyCallback = [](GLFWwindow* window, int key, int scancode, int action, int mods) {
		//Keyboard& keyboard = Application::get().getKeyboard();
		//keyboard.keys[key] = action != GLFW_RELEASE;
	};

	auto charCallback = [](GLFWwindow* window, unsigned int codePoint) {

	};

	glfwSetKeyCallback(*EventCallback::getWindow(), keyCallback);
	glfwSetCharCallback(*EventCallback::getWindow(), charCallback);

	keys = new bool[GLFW_KEY_LAST];
	for (int i = 0; i < GLFW_KEY_LAST; i++)
		keys[i] = false;
}

void KeyboardCallback::updateCallbackEvent() {

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

