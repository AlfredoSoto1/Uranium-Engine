#pragma once

struct GLFWwindow;

namespace Uranium::Engine {
	class CallbackManager;
}

namespace Uranium::Input::Callbacks {

	class KeyboardCallback final {
	private:
		friend Engine::CallbackManager;
	
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

	public:
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
		KeyboardCallback& operator=(const KeyboardCallback&) = delete;

	private:
		/*
		* Keyboard Callback constructor
		* creates all the monitor related callbacks
		*/
		explicit KeyboardCallback() noexcept;

	private:
		bool* keys;
		bool toggled;
		bool released;
	};
}