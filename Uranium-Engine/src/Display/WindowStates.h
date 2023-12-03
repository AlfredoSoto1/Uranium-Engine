#pragma once


namespace Uranium::Display {

	extern class Window;
	
	class WindowStates final {
	public:
		/*
		* Constructs a WindowState object with default values.
		* Initializes the state to a restored window.
		*/
		explicit WindowStates(Window* window) noexcept;

	public:
		/*
		* Call any window state
		*/
		void restore();
		void maximize();
		void minimize();
		void setFullscreen(bool fullscreen);

	public:
		/*
		* Get window states
		*/
		bool isRestored()  const;
		bool isMaximized() const;
		bool isMinimized() const;
		bool isFullscreen() const;

	private:
		/*
		* Window Reference
		*/
		Window* window;
		
		/*
		* General States
		*/
		bool restored;
		bool maximized;
		bool minimized;
		bool fullscreen;
	};
}