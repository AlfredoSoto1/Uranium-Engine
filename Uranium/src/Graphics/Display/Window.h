#pragma once

struct GLFWwindow;

namespace Uranium::Core {
	class Application;
}

namespace Uranium::Input::Listeners {
	class WindowListener;
}

namespace Uranium::Input::Callbacks {
	class WindowCallback;
}

namespace Uranium::Graphics::Display {

	class Monitor;
	class WindowMode;
	class WindowProps;

	/*
	* Window class
	* 
	*/
	class Window {
	public:
		/*
		* Custom alias
		*/
		using Application = Core::Application;

		using WindowCallback = Input::Callbacks::WindowCallback;
		using WindowListener = Input::Listeners::WindowListener;

	public:
		/*
		* Minimun and maximum default dimensions
		* for a window when resizing and creation
		*/
		static const unsigned int MIN_WIDTH = 320;
		static const unsigned int MIN_HEIGHT = 180;

	public:
		explicit Window();
		
		~Window();

		auto getModes()    -> WindowMode&;
		auto getProps()    -> WindowProps&;
		auto getCallback() -> WindowCallback&;

	public:
		/*
		* Public methods that cannot
		* be called without window being
		* created first.
		*/
		void close();
		void focus();			
		void requestAttention();

		void centerWindow(const Monitor& monitor);

		bool isCurrent() const;
		bool shouldClose() const;

		operator GLFWwindow* () const;

	public:
		/*
		* Public methods that can
		* be called without the window being
		* created first
		*/
		auto getWindowListener() const-> WindowListener*;

		void setWindowListener(WindowListener* windowListener);

	private:
		/*
		* friends with other classes
		*/
		friend Application;
		friend WindowCallback;

	private:
		/*
		* Private methods
		*/
		void build();
		void dispose();

	private:
		/*
		* Private members
		*/
		volatile bool hasCreated;
		volatile bool hasDisposed;

		GLFWwindow* glWindow;
		WindowListener* windowListener;

		WindowMode* windowMode;   // Window current modes
		WindowProps* windowProps; // Window current properties
		WindowCallback* callback; // Window callbacks
	};
}