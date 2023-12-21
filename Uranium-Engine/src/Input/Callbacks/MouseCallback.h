#pragma once

struct GLFWwindow;

namespace Uranium::Engine {
	class CallbackManager;
}

namespace Uranium::Input::Callbacks {

	class MouseCallback final {
	private:
		friend Engine::CallbackManager;

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

	public:
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
		MouseCallback& operator=(const MouseCallback&) = delete;

	private:
		/*
		* Mouse Callback constructor
		* creates all the mouse related callbacks
		*/
		explicit MouseCallback() noexcept;
		
	private:
		/*
		* Array of all mouse buttons available by GLFW
		*/
		bool* mouseButtons;
	};
}