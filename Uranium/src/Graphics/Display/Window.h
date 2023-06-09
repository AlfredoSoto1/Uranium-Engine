#pragma once

#include <memory>
#include <string>

struct GLFWwindow;

namespace Uranium::Input::Callbacks {
	class WindowCallback;
}

namespace Uranium::Graphics::Display {

	class Monitor;
	class WindowProps;

	class Window {
	public:
		/*
		* Custom alias
		*/
		using WindowCallback = Uranium::Input::Callbacks::WindowCallback;

	public:
		Window(const std::string& title, unsigned int width, unsigned int height);
		virtual ~Window();

		void setMonitor(std::shared_ptr<Monitor> monitor);
		
		operator GLFWwindow* ();
		
		WindowProps& getProperties();
		std::shared_ptr<Monitor> getMonitor();

	public:
		/*
		* public methods
		*/

		bool hasClosed();
		bool failedOnCreation();

		void init();				// 
		void close();				// main methods that controls
		void dispose();				// the initialization and finalization of window
		
		void focus();				// 
		void restore();				// These are the basic integrated window
		void maximize();			// commands used for modifying the aspect
		void minimize();			// of the window itself
		void requestAttention();	// 
		void centerWindow();		// 

		// set fullscreen with a resolution
		void fullscreen(unsigned int width, unsigned int height);
		
	private:
		/*
		* Friend with other classes
		*/
		friend WindowProps;
		friend WindowCallback;

	private:
		/*
		* Private methods
		*/
		void prepareWindowHints();		//
		void prepareWindowGLVersion();	// Constructs window hints beforea
		void prepareContextHints();		// and after creation.

		void createWindow();

	private:
		/*
		* Private members
		*/
		bool hasFailed;
		bool hasDisposed;
		
		GLFWwindow* window;
		WindowProps* windowProps;

		std::shared_ptr<Monitor> monitor;
	};
}