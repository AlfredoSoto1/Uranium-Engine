#pragma once

#include "WindowMode.h"
#include "WindowProps.h"

struct GLFWwindow;

namespace Uranium::Core {
	class Application;
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

	public:
		/*
		* Minimun and maximum default dimensions
		* for a window when resizing and creation
		*/
		static const unsigned int MIN_WIDTH = 320;
		static const unsigned int MIN_HEIGHT = 180;

	public:
		explicit Window(
			const WindowProps& windowProps,
			const WindowMode& windowMode
		);
		
		~Window();

	public:
		/*
		* Public methods that can
		* be called without window
		* creation.
		*/
		void restore();			
		void maximize();		
		void minimize();		

		void fullscreen(const Monitor& monitor);

		bool hasResized();
		
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
		GLFWwindow* glWindow;
		
		WindowMode windowMode;
		WindowProps windowProps;

		bool resized;
		bool hasDisposed;
	};
}