#include <GLFW/glfw3.h>

#include "CursorCallback.h"
#include "Platform/Display/Window.h"

namespace Uranium::Input::Callbacks {

	CursorCallback::CursorCallback(Window* window) noexcept :
		cursorMoved(0, 0),
		cusorEntered(false),
		cursorDropped()
	{
		glfwSetDropCallback(*window,        CursorCallback::drop_callback);
		glfwSetCursorPosCallback(*window,   CursorCallback::moved_callback);
		glfwSetCursorEnterCallback(*window, CursorCallback::entered_callback);
	}

	void CursorCallback::drop_callback(GLFWwindow* glWindow, int pathCount, const char** paths) {
		using namespace Events;
		Window& window = *(Window*)glfwGetWindowUserPointer(glWindow);

		window.cursorCallback->cursorDropped.droppedPaths.clear();

		for(int i = 0; i < pathCount;i++)
			window.cursorCallback->cursorDropped.droppedPaths.push_back(paths[i]);

		window.callbackFunction(window.cursorCallback->cursorDropped);
	}

	void CursorCallback::entered_callback(GLFWwindow* glWindow, int isInside) {
		using namespace Events;
		Window& window = *(Window*)glfwGetWindowUserPointer(glWindow);

		window.cursorCallback->cusorEntered.entered = isInside > 0;
		window.callbackFunction(window.cursorCallback->cusorEntered);
	}

	void CursorCallback::moved_callback(GLFWwindow* glWindow, double xpos, double ypos) {
		using namespace Events;
		Window& window = *(Window*)glfwGetWindowUserPointer(glWindow);

		window.cursorCallback->cursorMoved.x_position = xpos;
		window.cursorCallback->cursorMoved.y_position = ypos;
		window.cursorCallback->cursorMoved.x_normalPosition =  (xpos * 2.0) / window.props.dimension.x - 1.0;
		window.cursorCallback->cursorMoved.y_normalPosition = -(ypos * 2.0) / window.props.dimension.y + 1.0;

		window.callbackFunction(window.cursorCallback->cursorMoved);
	}
}