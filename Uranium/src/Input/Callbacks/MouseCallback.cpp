#include <iostream>
#include <GLFW/glfw3.h>

#include "MouseCallback.h"
#include "Graphics/Display/Window.h"

using namespace Uranium::Input::Callbacks;
using namespace Uranium::Graphics::Display;

MouseCallback::MouseCallback(Window* window) :
	EventCallback(window)
{
	// initiate callbacks
	initCallbacks();
}

MouseCallback::~MouseCallback() {
	delete[] mouseButtons;
}

void MouseCallback::initCallbacks() {
	auto clickCallback = [](GLFWwindow* winPtr, int button, int action, int mods) {
		//Mouse& mouse = Application::get().getMouse();
		//Cursor& cursor = mouse.getCursor();

		//mouse.mouseButtons[button] = action != GLFW_RELEASE;
	};

	auto scrollCallback = [](GLFWwindow* winPtr, double xOffset, double yOffset) {
		//Mouse& mouse = Application::get().getMouse();
	};

	auto positionCallback = [](GLFWwindow* winPtr, double xpos, double ypos) {
		//Window& window = Application::get().getWindow();
		//Mouse& mouse = Application::get().getMouse();
		//Cursor& cursor = mouse.getCursor();

		//cursor.changePosition(xpos, ypos);
		//cursor.changeNormPosition((xpos * 2.0) / window.getSettings().getWidth() - 1.0, -(ypos * 2.0) / window.getSettings().getHeight() + 1.0);
	};

	// set glfw mouse callbacks
	glfwSetScrollCallback(*EventCallback::getWindow(), scrollCallback);
	glfwSetCursorPosCallback(*EventCallback::getWindow(), positionCallback);
	glfwSetMouseButtonCallback(*EventCallback::getWindow(), clickCallback);

	// create bool array containing
	// mouse button activation flag
	// for each button when being interacted with
	mouseButtons = new bool[GLFW_MOUSE_BUTTON_LAST];
}

void MouseCallback::updateCallbackEvent() {

}


bool MouseCallback::isButtonDown(int button) {
	if (button < 0)
		return false;
	return mouseButtons[button] ? true : false;
}

int MouseCallback::isMouseToggled(int button) {
	return 0;
}
