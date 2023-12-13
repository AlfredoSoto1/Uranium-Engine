#pragma once

struct GLFWwindow;

namespace Uranium::Services {
	extern class BaseEngine;
}

namespace Uranium::Input::Callbacks {

	class MouseCallback final {
	private:
		/*
		* Friends with other classes
		*/
		friend class Services::BaseEngine;

	public:
		/*
		* Returns true if a mouse button is being hold down
		*/
		bool isButtonDown(int button);
	
	private:
		/*
		* It gets called when the mouse gets clicked
		*/
		static void clickEvent(GLFWwindow* window, int button, int action, int mods);
		
		/*
		* It gets called when the mouse gets moved
		*/
		static void movedEvent(GLFWwindow* window, double xpos, double ypos);
		
		/*
		* It gets called when the mouse uses the scroll wheel
		*/
		static void scrollEvent(GLFWwindow* window, double xOffset, double yOffset);

	private:
		/*
		* Mouse Callback constructor
		* creates all the mouse related callbacks
		*/
		explicit MouseCallback() noexcept;
		
		~MouseCallback();

		/*
		* Copy and move constructor deleted
		* this is beacause we dont want the client
		* to move or copy this class by accident since
		* the one who must have ownership of this class
		* instance is the engine only.
		*/
		MouseCallback(MouseCallback&) = delete;
		MouseCallback(MouseCallback&&) = delete;
		MouseCallback(const MouseCallback&) = delete;
		MouseCallback(const MouseCallback&&) = delete;

	private:
		/*
		* Array of all mouse buttons available by GLFW
		*/
		bool* mouseButtons;
	};
}