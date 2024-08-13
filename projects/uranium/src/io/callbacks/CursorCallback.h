#pragma once
#include "core/URAPI.h"
#include "Input/Events/CursorMovedEvent.h"
#include "Input/Events/CursorEnteredEvent.h"
#include "Input/Events/CursorDroppedEvent.h"

struct GLFWwindow;

namespace uranium::io::callbacks {

	URANIUM_API class CursorCallback final {
	public:
		explicit CursorCallback(Window* window) noexcept;
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

	private:
		Events::CursorMovedEvent cursorMoved;
		Events::CursorEnteredEvent cusorEntered;
		Events::CursorDroppedEvent cursorDropped;

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
	};
}