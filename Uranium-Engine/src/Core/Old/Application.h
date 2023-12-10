#pragma once

#include <memory>
#include <thread>
#include <vector>

namespace Uranium::Graphics::Display {
	class Window;
	class Monitor;
}

namespace Uranium::Core {

	class EntryPoint;

	/*
	* Application blueprint
	* 
	*/
	class Application {
	public:
		/*
		* Custom alias
		*/
		using Thread = std::thread;
		using Window = Graphics::Display::Window;
		using Monitor = Graphics::Display::Monitor;

	public:
		/*
		* public static declarations
		*/
		static Application* instance();

	private:
		/*
		* private static declarations
		*/
		static Application* instanceReference;
		
		// Delaration of glfw error callback
		static void errorCallbackReceive(int error, const char* description);
		
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
		* public members
		*/
		volatile bool isGLFWActive();
		volatile bool hasAppStarted();

		void exit();

		void registerWindow(std::shared_ptr<Window> window);

	private:
		/*
		* Friend with other classes
		*/
		friend Window;
		friend EntryPoint;

	private:
		/*
		* private methods
		*/
		void run();

		void update(std::shared_ptr<Window> window);

	private:
		/*
		* private members
		*/
		volatile bool exitRequested;
		volatile bool glfwInitiated;
		volatile bool applicationRunning;

		unsigned int activeContexts;

		std::vector<std::shared_ptr<Thread>> activeThreads;
	};
}