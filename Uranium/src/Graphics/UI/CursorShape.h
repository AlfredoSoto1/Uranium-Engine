#pragma once

struct GLFWcursor;
struct GLFWimage;

namespace Uranium::Graphics::UI {

	class CursorShape {
	public:
		CursorShape(int glfwCursor);
		CursorShape(GLFWimage* image);
		~CursorShape();

		operator GLFWcursor* ();
	private:
		/*
		* Private members
		*/
		int cursorType;

		GLFWcursor* cursor;

	};
}