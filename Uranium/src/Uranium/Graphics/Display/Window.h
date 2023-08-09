#pragma once

#include "WindowMode.h"
#include "WindowProps.h"

struct GLFWwindow;

namespace Uranium::Core {
	class Application;
}

namespace Uranium::Listeners {
	class WindowListener;
}

namespace Uranium::Callbacks {
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

		using WindowCallback = Callbacks::WindowCallback;
		using WindowListener = Listeners::WindowListener;

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

		WindowMode& getModes();
		WindowProps& getProps();

		auto getWindowListener() const -> WindowListener*;

		void setWindowListener(WindowListener* windowListener);

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

		bool isCurrent();
		bool shouldClose();

		operator GLFWwindow* () const;

	private:
		/*
		* friends with other classes
		*/
		friend Application;

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
		bool hasCreated;
		bool hasDisposed;

		GLFWwindow* glWindow;
		WindowCallback* callback;
		WindowListener* windowListener;

		WindowMode windowMode;
		WindowProps windowProps;
	};
}