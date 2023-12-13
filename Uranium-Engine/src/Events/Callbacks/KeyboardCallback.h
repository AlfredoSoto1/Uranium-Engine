#pragma once

struct GLFWwindow;

namespace Uranium::Core {
	extern class BaseEngine;
}

namespace Uranium::Events::Callbacks {

	class KeyboardCallback final {
	private:
		/*
		* Friends with other classes
		*/
		friend Core::BaseEngine;
	
	public:
		bool isKeyDown(int key);
		bool isKeyToggled(int key);
		bool isKeyReleased(int key);

	private:
		/*
		* Gets called when a key event happened
		*/
		static void keyEvent(GLFWwindow* window, int key, int scancode, int action, int mods);
		
		/*
		* Gets called when a char event happened
		*/
		static void charEvent(GLFWwindow* window, unsigned int codePoint);

	private:
		/*
		* Keyboard Callback constructor
		* creates all the monitor related callbacks
		*/
		explicit KeyboardCallback() noexcept;

		~KeyboardCallback();

		/*
		* Copy and move constructor deleted
		* this is beacause we dont want the client
		* to move or copy this class by accident since
		* the one who must have ownership of this class
		* instance is the engine only.
		*/
		KeyboardCallback(KeyboardCallback&) = delete;
		KeyboardCallback(KeyboardCallback&&) = delete;
		KeyboardCallback(const KeyboardCallback&) = delete;
		KeyboardCallback(const KeyboardCallback&&) = delete;

	private:
		bool* keys;
		bool toggled;
		bool released;
	};
}