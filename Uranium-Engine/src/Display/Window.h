#pragma once

#include "WindowModes.h"
#include "WindowProps.h"
#include "WindowStates.h"
#include "WindowEvents.h"

extern struct GLFWwindow;

namespace Uranium::Display {

	class Window final {
	private:
		/*
		* Friends with other classes
		*/
		friend class WindowModes;
		friend class WindowStates;

	public:
		/*
		* This creates a window inside an OpenGL context.
		* The distructor is not added to the virtual table
		* since no class should inherit from *this* class.
		*/
		explicit Window();

		~Window();

	
	public:
		//void centerWindow(const Monitor& monitor);

	private:
		void prepareDefaultHints() const;

	private:
		/*
		* Window members
		*/
		GLFWwindow* glWindow;
		
		WindowModes modes;
		WindowProps props;
		WindowStates states;
		WindowEvents events;

		unsigned int glMajor;
		unsigned int glMinor;

		volatile bool hasCreated;
	};
}