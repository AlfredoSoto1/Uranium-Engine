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
	* Mouse Callback blueprint
	* 
	*/
	class MouseCallback {
	public:
		/*
		* custom alias
		*/
		using Window = Uranium::Graphics::Display::Window;

	public:
		bool isButtonDown(int button);
		int isMouseToggled(int button);
	
	private:
		/*
		* Friend with other classes
		*/
		friend Core::UnitProgram;

	private:
		/*
		* Callback constructors
		*/
		MouseCallback(MouseCallback& copy) = delete;
		MouseCallback(MouseCallback&& move) = delete;
		MouseCallback(const MouseCallback& copy) = delete;
		MouseCallback(const MouseCallback&& move) = delete;

		explicit MouseCallback(Window* window);
		
		~MouseCallback();

	private:
		/*
		* Private static callbacks
		*/
		static void clickDetected(GLFWwindow* window, int button, int action, int mods);
		static void scrollDetected(GLFWwindow* window, double xOffset, double yOffset);
		static void positionDetected(GLFWwindow* window, double xpos, double ypos);

	private:
		/*
		* Private members
		*/
		// Use a raw pointer type since this class
		// will only be created once inside the parent Window
		// class. Meaning that this class cannot have a copy 
		// or can be moved out of the Window scope instance.
		Window* window;

		bool* mouseButtons;
	};
}