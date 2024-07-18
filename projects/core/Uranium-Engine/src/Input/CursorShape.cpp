#include <GLFW/glfw3.h>

#include "CursorShape.h"

namespace Uranium::Graphics::UI {

	CursorShape::CursorShape(int glfwCursor) :
		cursorType(glfwCursor),
		cursor(nullptr)
	{
		switch (cursorType) {
		case GLFW_IBEAM_CURSOR:
			cursor = glfwCreateStandardCursor(GLFW_IBEAM_CURSOR);
		case GLFW_HAND_CURSOR:
			cursor = glfwCreateStandardCursor(GLFW_HAND_CURSOR);
		case GLFW_CROSSHAIR_CURSOR:
			cursor = glfwCreateStandardCursor(GLFW_CROSSHAIR_CURSOR);
		case GLFW_HRESIZE_CURSOR:
			cursor = glfwCreateStandardCursor(GLFW_HRESIZE_CURSOR);
		case GLFW_VRESIZE_CURSOR:
			cursor = glfwCreateStandardCursor(GLFW_VRESIZE_CURSOR);
		default:
			cursor = glfwCreateStandardCursor(GLFW_ARROW_CURSOR);
		}
	}

	CursorShape::CursorShape(GLFWimage* image) {
		// FIXME
	}

	CursorShape::~CursorShape() {
		glfwDestroyCursor(cursor);
	}

	CursorShape::operator GLFWcursor* () {
		return cursor;
	}
}