#pragma once

struct GLFWimage;
struct GLFWcursor;

namespace Uranium::Graphics::UI {

	/*
	* Cursor shape blueprint
	*/
	class CursorShape {
	public:
		/*
		* Cursor shape constructors
		*/
		CursorShape() = delete;

		explicit CursorShape(int glfwCursor);
		explicit CursorShape(GLFWimage* image);

		~CursorShape();

	public:
		/*
		* public modifiers
		*/
		operator GLFWcursor* ();
	
	private:
		/*
		* Private members
		*/
		int cursorType;

		GLFWcursor* cursor;
	};
}