#pragma once

#include <memory>

namespace Uranium::Platform::Monitor {
	class Monitor;
}

namespace Uranium::Platform::Display {

	class WindowStates final {
	private:
		/*
		* Friends with other classes
		*/
		friend class Window;
		
	public:
		/*
		* No need of default constructor
		*/
		WindowStates() = delete;

	public:
		/*
		* Call any window state
		*/
		void restore();
		void maximize();
		void minimize();
		void setFullscreen(std::shared_ptr<Monitor::Monitor> monitor);

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
		* Constructs a WindowState object with default values.
		* Initializes the state to a restored window.
		*/
		explicit WindowStates(Window* window) noexcept;

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