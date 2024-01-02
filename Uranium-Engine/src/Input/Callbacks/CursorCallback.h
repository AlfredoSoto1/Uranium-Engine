#pragma once

#include "Input/Events/CursorEvent.h"

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
		static void drop_callback(GLFWwindow* glWindow, int pathCount, const char** paths);

		/*
		* Gets called if the cursor is inside the window
		*/
		static void entered_callback(GLFWwindow* glWindow, int isInside);

		/*
		* It gets called when the mouse gets moved
		*/
		static void moved_callback(GLFWwindow* glWindow, double xpos, double ypos);

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
		using Window = Platform::Display::Window;

		/*
		* Cursor Callback constructor
		* creates all the monitor related callbacks
		*/
		explicit CursorCallback(Window* window) noexcept;
	
	private:
		Events::CursorMovedEvent cursorMoved;
		Events::CursorEnteredEvent cusorEntered;
		Events::CursorDroppedEvent cursorDropped;
	};
}