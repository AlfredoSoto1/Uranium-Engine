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
	* Cursor Callback
	*/
	class CursorCallback {
	public:
		/*
		* custom alias
		*/
		using Window = Uranium::Graphics::Display::Window;

	private:
		/*
		* Mutual friend classes
		*/
		friend Core::UnitProgram;

	private:
		/*
		* Private methods
		*/
		CursorCallback(CursorCallback& copy) = delete;
		CursorCallback(CursorCallback&& move) = delete;
		CursorCallback(const CursorCallback& copy) = delete;
		CursorCallback(const CursorCallback&& move) = delete;

		explicit CursorCallback(Window* window);

		~CursorCallback();

	private:
		/*
		* Private static callbacks
		*/
		static void dropDetected(GLFWwindow* window, int pathCount, const char** paths);
		static void enteredDetected(GLFWwindow* window, int isInside);

	private:
		/*
		* Private members
		*/
		// Use a raw pointer type since this class
		// will only be created once inside the parent Window
		// class. Meaning that this class cannot have a copy 
		// or can be moved out of the Window scope instance.
		Window* window;
	};
}