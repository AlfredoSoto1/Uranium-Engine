#pragma once
#include "core/URAPI.h"

#include "Input/Events/KeyPressedEvent.h"
#include "Input/Events/KeyReleasedEvent.h"

struct GLFWwindow;

namespace uranium::io::callbacks {

	class KeyboardCallback final {
	public:
		explicit KeyboardCallback(Window* window) noexcept;
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

	private:
		Events::KeyPressedEvent keyPressedEvent;
		Events::KeyReleasedEvent keyReleasedEvent;

	private:
		/*
		* Gets called when a key event happened
		*/
		static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
	};
}