#pragma once

#include "Monitor.h"
#include "WindowHint.h"
#include "WindowMode.h"
#include "WindowProps.h"

struct GLFWwindow;

namespace Uranium::Graphics::Display {

	class Monitor;
	class WindowMode;
	class WindowProps;
	enum class WindowHint;

	/*
	* Window class
	* 
	*/
	class Window {
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
			const WindowMode& windowMode,
			const Monitor& monitor
		);
		
		~Window();

		void create();
		void dispose();

		void setHint(const WindowHint& hint);

	public:
		/*
		* Public methods that can
		* be called without window
		* creation.
		*/
		void restore();			
		void maximize();		
		void minimize();		
		void fullscreen();

		bool hasResized();

	public:
		/*
		* Public methods that cannot
		* be called without window being
		* created first.
		*/
		void close();
		void focus();			
		void centerWindow();
		void requestAttention();

	private:
		/*
		* Private members
		*/
		GLFWwindow* glWindow;
		
		Monitor monitor;
		WindowMode windowMode;
		WindowProps windowProps;

		bool resized;
	};
}