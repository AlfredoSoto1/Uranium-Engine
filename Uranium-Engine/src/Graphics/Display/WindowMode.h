#pragma once

struct GLFWwindow;

namespace Uranium::Input::Callbacks {
	class WindowCallback;
}

namespace Uranium::Graphics::Display {

	class Window;
	class Monitor;

	/*
	* Window Modes blueprint
	*/
	class WindowMode {
	public:
		/*
		* custom alias
		*/
		using WindowCallback = Input::Callbacks::WindowCallback;

	public:
		/*
		* public setter modes
		*/
		void setVisible(bool visible);
		void setResizable(bool resizable);
		void setDecorated(bool decorated);
		void setAlwaysOnTop(bool alwaysOnTop);

		void setFullscreen(const Monitor& monitor);

	public:
		/*
		* Public methods that can
		* be called without window
		* creation.
		*/
		void restore();
		void maximize();
		void minimize();

	private:
		/*
		* Friends with other classes
		*/
		friend Window;
		friend WindowCallback;

	private:
		/*
		* Private Mode constructor
		*/
		explicit WindowMode();

		void initDefault() const;

	private:
		/*
		* private members
		*/
		GLFWwindow* glWindow;

	private:
		/*
		* Private modes
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
