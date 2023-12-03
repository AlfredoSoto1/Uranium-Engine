#pragma once

namespace Uranium::Display {

	extern class Window;

	class WindowModes final {
	public:
		/*
		* Constructs a WindowModes object with default values.
		* Initializes the modes to a default.
		*/
		explicit WindowModes(Window* window) noexcept;

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