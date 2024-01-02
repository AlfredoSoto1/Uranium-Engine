#pragma once

struct GLFWwindow;

namespace Uranium::Platform::Display {
	class Window;
}

namespace Uranium::Input::Callbacks {

	class WindowCallback final {
	private:
		/*
		* Called when window close is requested
		*/
		static void close_callback(GLFWwindow* glWindow);

		/*
		* Called when window is moved or resized
		*/
		static void position_callback(GLFWwindow* glWindow, int xpos, int ypos);
		static void resized_callback(GLFWwindow* glWindow, int width, int height);

		/*
		* Called when the window is on or out of focus
		*/
		static void focus_callback(GLFWwindow* glWindow, int isFocused);

		/*
		* Called when the window gets minimized, maximized or fullscreen
		*/
		static void minimize_callback(GLFWwindow* glWindow, int isMinimized);
		static void maximize_callback(GLFWwindow* glWindow, int isMaximized);

		/*
		* Called when the window canvas gets refreshed
		*/
		static void refresh_callback(GLFWwindow* glWindow);
		static void framebuffer_resize_callback(GLFWwindow* glWindow, int width, int height);

	public:
		~WindowCallback() = default;

		/*
		* Copy and move constructor deleted
		* this is beacause we dont want the client
		* to move or copy this class by accident since
		* the one who must have ownership of this class
		* instance is the engine only.
		*/
		WindowCallback(WindowCallback&) = delete;
		WindowCallback(WindowCallback&&) = delete;
		WindowCallback& operator=(const WindowCallback&) = delete;

	public:
		using Window = Platform::Display::Window;

		/*
		* Window Callback constructor
		* creates all the window related callbacks
		*/
		explicit WindowCallback(Window* window) noexcept;
	};
}