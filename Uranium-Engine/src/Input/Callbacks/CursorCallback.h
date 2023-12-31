#pragma once

struct GLFWwindow;

namespace Uranium::Platform::Display {
	class Window;
}

namespace Uranium::Input::Callbacks {

	class CursorCallback final {
	private:
		/*
		* Gets called when a link or file is dropped in window
		*/
		static void dropEvent(GLFWwindow* window, int pathCount, const char** paths);

		/*
		* Gets called if the cursor is inside the window
		*/
		static void enteredEvent(GLFWwindow* window, int isInside);

	public:
		~CursorCallback() = default;

		/*
		* Copy and move constructor deleted
		* this is beacause we dont want the client
		* to move or copy this class by accident since
		* the one who must have ownership of this class
		* instance is the engine only.
		*/
		CursorCallback(CursorCallback&) = delete;
		CursorCallback(CursorCallback&&) = delete;
		CursorCallback& operator=(const CursorCallback&) = delete;

	public:
		/*
		* Cursor Callback constructor
		* creates all the monitor related callbacks
		*/
		explicit CursorCallback(Platform::Display::Window* window) noexcept;

	};
}