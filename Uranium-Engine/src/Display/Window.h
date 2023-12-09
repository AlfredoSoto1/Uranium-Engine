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
		friend class WindowProps;
		friend class WindowModes;
		friend class WindowStates;
		friend class WindowEvents;

	public:
		/*
		* This creates a window inside an OpenGL context.
		* The distructor is not added to the virtual table
		* since no class should inherit from *this* class.
		*/
		explicit Window() noexcept;

		~Window();
	
	public:
		/*
		* 
		*/
		operator GLFWwindow* () const;

		/*
		* 
		*/
		bool isCurrent() const;

	private:
		void prepareDefaultHints() const;

	private:
		/*
		* GLFW window reference
		*/
		GLFWwindow* glWindow;
		
		/*
		* Window content members
		*/
		WindowModes modes;
		WindowProps props;
		WindowStates states;
		WindowEvents events;

		/*
		* GL - context version
		*/
		unsigned int glMajor;
		unsigned int glMinor;

		volatile bool hasCreated;
	};
}