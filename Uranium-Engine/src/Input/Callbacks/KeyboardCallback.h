#pragma once

#include "Input/Events/KeyEvents.h"

struct GLFWwindow;

namespace Uranium::Platform::Display {
	class Window;
}

namespace Uranium::Input::Callbacks {

	class KeyboardCallback final {
	private:
		/*
		* Gets called when a key event happened
		*/
		static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
		
	public:
		~KeyboardCallback() = default;

		/*
		* Copy and move constructor deleted
		* this is beacause we dont want the client
		* to move or copy this class by accident since
		* the one who must have ownership of this class
		* instance is the engine only.
		*/
		KeyboardCallback(KeyboardCallback&) = delete;
		KeyboardCallback(KeyboardCallback&&) = delete;
		KeyboardCallback& operator=(const KeyboardCallback&) = delete;

	public:
		using Window = Platform::Display::Window;

		/*
		* Keyboard Callback constructor
		* creates all the monitor related callbacks
		*/
		explicit KeyboardCallback(Window* window) noexcept;

	private:
		Events::KeyPressedEvent keyPressedEvent;
		Events::KeyReleasedEvent keyReleasedEvent;
	};
}