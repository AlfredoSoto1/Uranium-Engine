#pragma once

namespace Uranium::Platform::Display {

	class WindowModes final {
	private:
		/*
		* Friends with other classes
		*/
		friend class Window;

	public:
		/*
		* No need of default constructor
		*/
		WindowModes() = delete;

	public:
		/*
		* Get window modes
		*/
		auto isVisible()     const -> bool;
		auto isResizable()   const -> bool;
		auto isDecorated()   const -> bool;
		auto isAlwaysOnTop() const -> bool;
		
	public:
		/*
		* Set window modes
		*/
		void setVisible(bool visible);
		void setResizable(bool resizable);
		void setDecorated(bool decorated);
		void setAlwaysOnTop(bool alwaysOnTop);

	private:
		/*
		* Constructs a WindowModes object with default values.
		* Initializes the modes to a default.
		*/
		explicit WindowModes(Window* window) noexcept;

	private:
		/*
		* Window reference
		*/
		Window* window;

		/*
		* General Modes
		*/
		bool visible;
		bool resizable;
		bool decorated;
		bool alwaysOnTop;
	};
}