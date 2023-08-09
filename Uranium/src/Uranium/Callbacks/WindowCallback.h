#pragma once

struct GLFWwindow;

namespace Uranium::Graphics::Display {
	class Window;
}

namespace Uranium::Callbacks {

	/*
	* Window Callback blueprint
	* 
	*/
	class WindowCallback {
	public:
		/*
		* Custom alias
		*/
		using Window = Graphics::Display::Window;

	private:
		/*
		* Friend with other classes
		*/
		friend Window;
		
	private:
		/*
		* Callback constructor
		*/
		WindowCallback(WindowCallback& copy) = delete;
		WindowCallback(WindowCallback&& move) = delete;
		WindowCallback(const WindowCallback& copy) = delete;
		WindowCallback(const WindowCallback&& move) = delete;

		explicit WindowCallback(Window* window);
		
		~WindowCallback();

	private:
		/*
		* Private static callbacks
		*/
		static void windowClose(GLFWwindow* glWindow);
		static void sizeChange(GLFWwindow* glWindow, int width, int height);
		static void positionChange(GLFWwindow* glWindow, int xpos, int ypos);

		static void onFocus(GLFWwindow* glWindow, int isFocused);
		static void minimize(GLFWwindow* glWindow, int isMinimized);
		static void maximize(GLFWwindow* glWindow, int isMaximized);

		static void canvasRefresh(GLFWwindow* glWindow);
		static void frameBufferSize(GLFWwindow* glWindow, int width, int height);

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