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
		explicit Window();
		
		~Window();

		WindowMode& getModes();
		WindowProps& getProps();

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
		bool hasDisposed;

		GLFWwindow* glWindow;
		
		WindowMode windowMode;
		WindowProps windowProps;
	};
}