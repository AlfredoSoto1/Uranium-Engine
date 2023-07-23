#pragma once

namespace Uranium::Core {

	class ApplicationThreadPool;

	/*
	* 
	*/
	class Application {
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
		* Public modifiers from Application
		*/

	public:
		/*
		* Public methods
		*/

	private:
		/*
		* Private modifiers
		*/
		ApplicationThreadPool* threadPool;

	private:
		/*
		* Private methods
		*/

	};
}