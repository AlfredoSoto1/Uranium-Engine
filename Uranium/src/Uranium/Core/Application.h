#pragma once

#include <memory>
#include <thread>
#include <vector>

namespace Uranium::Graphics::Display {
	class Monitor;
}

namespace Uranium::Callbacks {
	class MonitorCallback;
}

namespace Uranium::Core {

	class EntryPoint;

	/*
	* 
	*/
	class Application {
	public:
		/*
		* Custom alias
		*/
		using thread = std::thread;
		using Monitor = Graphics::Display::Monitor;
		using MonitorCallback = Callbacks::MonitorCallback;

	public:
		/*
		* public static declarations
		*/
		static volatile bool isGLFWActive();
		static volatile bool hasAppStarted();

	private:
		/*
		* private static declarations
		*/
		static volatile bool glfwInitiated;
		static volatile bool applicationStarted;

		static void errorCallbackReceive(int error, const char* description);
	
	private:
		/*
		* Friend with other classes
		*/
		friend EntryPoint;

	public:
		/*
		* Declaration of the main
		* application for the Uranium Engine
		* 
		* This runs out of OpenGL's context
		*/
		explicit Application();

		Application(Application&) = delete;		   // Delete all the copy/move construtors
		Application(Application&&) = delete;	   // This is to prevent the client to copy or move
		Application(const Application&) = delete;  // an instance of the application singleton 
		Application(const Application&&) = delete; // 

		/*
		* Frees the memory created by the application.
		* This does NOT frees memory allocated by OpenGL
		* OpenGL disposal is done in its local thread context
		*/
		virtual ~Application();

	public:
		/*
		* public methods
		*/

		// Returns a monitor
		Monitor getPrimaryMonitor();

		// Return a vector containing all
		// the connected monitors to the PC
		// If no monitors are connected, vector will be empty
		std::vector<Monitor> getConnectedMonitors();

	private:
		/*
		* private methods
		*/
		void run();

		void createCallbacks();

	private:
		/*
		* private members
		*/
		MonitorCallback* monitorCallback;
	};
}