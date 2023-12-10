#pragma once

struct GLFWwindow;

namespace Uranium::Display {
	extern class Window;
}

namespace Uranium::Callbacks {

	class WindowCallback final {
	public:
		/*
		* Public modifiers
		*/
		auto hasFocused() const -> volatile bool;
		auto hasResized() const -> volatile bool;
	
		void setHasResized(bool resized);

	public:
		explicit WindowCallback(Display::Window* window);
		
		~WindowCallback();
	private:
		/*
		* Delete the callback copy and move constructors
		*/
		WindowCallback(WindowCallback& copy) = delete;
		WindowCallback(WindowCallback&& move) = delete;
		WindowCallback(const WindowCallback& copy) = delete;
		WindowCallback(const WindowCallback&& move) = delete;

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

		volatile bool focused;
		volatile bool resized;
	};
}