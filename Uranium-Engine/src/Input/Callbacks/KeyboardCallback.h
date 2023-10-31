#pragma once

struct GLFWwindow;

namespace Uranium::Core {
	class UnitProgram;
}

namespace Uranium::Graphics::Display {
	class Window;
}

namespace Uranium::Input::Callbacks {

	/*
	* Keyboard Callback
	*/
	class KeyboardCallback {
	public:
		/*
		* Custom alias
		*/
		using Window = Uranium::Graphics::Display::Window;

	public:
		bool isKeyDown(int key);
		bool isKeyToggled(int key);
		bool isKeyReleased(int key);

	private:
		/*
		* Mutual friend classes
		*/
		friend Core::UnitProgram;

	private:
		/*
		* Private methods
		*/
		KeyboardCallback(KeyboardCallback& copy) = delete;
		KeyboardCallback(KeyboardCallback&& move) = delete;
		KeyboardCallback(const KeyboardCallback& copy) = delete;
		KeyboardCallback(const KeyboardCallback&& move) = delete;

		explicit KeyboardCallback(Window* window);

		~KeyboardCallback();

	private:
		/*
		* Private static callbacks
		*/
		static void keyDetected(GLFWwindow* window, int key, int scancode, int action, int mods);
		static void charDetected(GLFWwindow* window, unsigned int codePoint);

	private:
		/*
		* Private members
		*/
		// Use a raw pointer type since this class
		// will only be created once inside the parent Window
		// class. Meaning that this class cannot have a copy 
		// or can be moved out of the Window scope instance.
		Window* window;

		bool* keys;
		bool toggled;
		bool released;
	};
}