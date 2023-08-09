#pragma once

struct GLFWwindow;

namespace Uranium::Callbacks {
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
		using WindowCallback = Callbacks::WindowCallback;

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

	public:
		/*
		* public getters
		*/
		inline bool hasResized() const;

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
		bool resized;

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
