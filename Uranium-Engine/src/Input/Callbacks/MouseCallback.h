#pragma once

#include "Input/Events/MouseScrollEvent.h"
#include "Input/Events/MouseButtonPressedEvent.h"
#include "Input/Events/MouseButtonReleasedEvent.h"

struct GLFWwindow;

namespace Uranium::Platform::Display {
	class Window;
}

namespace Uranium::Input::Callbacks {

	class MouseCallback final {
	private:
		/*
		* It gets called when the mouse button is pressed
		*/
		static void button_callback(GLFWwindow* glWindow, int button, int action, int mods);
		
		/*
		* It gets called when the mouse uses the scroll wheel
		*/
		static void scroll_callback(GLFWwindow* glWindow, double xOffset, double yOffset);

	public:
		~MouseCallback() = default;

		/*
		* Copy and move constructor deleted
		* this is beacause we dont want the client
		* to move or copy this class by accident since
		* the one who must have ownership of this class
		* instance is the engine only.
		*/
		MouseCallback(MouseCallback&) = delete;
		MouseCallback(MouseCallback&&) = delete;
		MouseCallback& operator=(const MouseCallback&) = delete;

	public:
		using Window = Platform::Display::Window;

		/*
		* Mouse Callback constructor
		* creates all the mouse related callbacks
		*/
		explicit MouseCallback(Window* window) noexcept;
		
	private:
		Events::MouseScrollEvent scroll;
		Events::MouseButtonPressedEvent pressed;
		Events::MouseButtonReleasedEvent released;
	};
}