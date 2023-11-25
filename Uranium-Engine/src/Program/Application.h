#pragma once

#include <memory>
#include <vector>
#include <string>
#include <stdexcept>

namespace Uranium::Program {

	extern class Context;

	class Application final {
	public:
		/*
		* Build the application at the default
		* entry point (main function).
		*/
		static void build(int argc, char* argv[], std::unique_ptr<Application> createdApplication);

		/*
		* Return the Application instance from singleton
		*/
		static Application& instance();

	private:
		/*
		* private static declarations
		*/
		static std::unique_ptr<Application> application;

		/*
		* Default method that logs any GL errors
		*/
		static void diagnosticErrors(int error, const char* description);

	public:
		/*
		* Application main constructor.
		* This must not throw an exception since this
		* is all what it must start from the application.
		*/
		explicit Application() noexcept;

		/*
		* Frees the memory created by the application.
		* This does NOT frees memory allocated by OpenGL
		* OpenGL disposal is done in its local thread context
		*/
		~Application();

		/*
		* Delete all the copy constructors since 
		* we dont want the client to create a copy
		* of the Application itself.
		*/
		Application(Application&) = delete;
		Application(const Application&) = delete;

	public:
		/*
		* public modifiers
		*/
		
		/*
		* Adds a new context reference to the application
		*/
		void addContext(std::unique_ptr<Context> context);

		/*
		* Forces the application to exit
		*/
		void exit();
		
		/*
		* Returns true if the application
		* has terminated
		*/
		inline bool hasTerminated() const;

	private:
		/*
		* private methods
		*/

		/*
		* Adds an argument from terminal when program starts
		*/
		void addArgument(const std::string& arg);

		/*
		* Runs the application content
		*/
		void run();

	private:
		/*
		* private members
		*/
		volatile bool exitRequested;

		std::vector<std::string> arguments;
		std::vector<std::unique_ptr<Context>> contexts;
	};
}