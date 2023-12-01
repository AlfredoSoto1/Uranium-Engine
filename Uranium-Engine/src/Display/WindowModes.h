#pragma once

namespace Uranium::Display {

	class WindowModes final {
	public:
		/*
		* Constructs a WindowModes object with default values.
		* Initializes the modes to a default.
		*/
		explicit WindowModes() noexcept;

	public:
		/*
		* Get window modes
		*/
		auto isVisible()     const -> bool;
		auto isResizable()   const -> bool;
		auto isDecorated()   const -> bool;
		auto isFullscreen()  const -> bool;
		auto isAlwaysOnTop() const -> bool;
		
	public:
		/*
		* Set window modes
		*/
		void setVisible(bool visible);
		void setResizable(bool resizable);
		void setDecorated(bool decorated);
		void setFullscreen(bool fullscreen);
		void setAlwaysOnTop(bool alwaysOnTop);

	private:
		/*
		* General Modes
		*/
		bool visible;
		bool resizable;
		bool decorated;
		bool fullscreen;
		bool alwaysOnTop;

		bool maximized;
		bool minimized;
	};
}