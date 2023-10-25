#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

import Uranium.Display.Window;

namespace Uranium::Display {

	Window::Window() :
		/*
		* Volatile members
		*/
		hasCreated(false),
		hasDisposed(false),

		/*
		* Window properties
		*/
		glWindow(nullptr),

		title("Default Window"),

		position(0, 0),
		dimension(MIN_WIDTH, MIN_HEIGHT),
		resolution(MIN_WIDTH, MIN_HEIGHT),

		opacity(100),

		// These are the minimum versions
		// of OpenGL that this application can
		// support by default
		glMajor(3),
		glMinor(3),

		/*
		* Window modes
		*/
		visible(true),
		resizable(true),
		decorated(true),
		fullscreen(false),
		alwaysOnTop(false),

		maximized(false),
		minimized(false)
	{
	
	}

	Window::~Window() {

	}

}