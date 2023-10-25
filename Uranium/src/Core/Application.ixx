export module Uranium.Core.Application;

import <memory>;
import <vector>;
import <string>;

export namespace Uranium::Core {

	extern class Context;

	class Application {
	public:
		/*
		* static declarations
		*/
		static Application& instance();

		/*
		* Build the application at the default
		* entry point (main function).
		*/
		static void build(int argc, char* argv[], std::unique_ptr<Application> application);
	
	private:
		/*
		* private static declarations
		*/
		static Application* instanceReference;

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
		virtual ~Application();

		/*
		* Delete all the moving/copying constructors
		* since we dont want the client to create a copy
		* of the Application itself.
		*/
		Application(Application&) = delete;
		Application(Application&&) = delete;
		Application(const Application&) = delete;
		Application(const Application&&) = delete;

	public:
		/*
		* public modifiers
		*/

		/*
		* Forces the application to exit
		*/
		void exit();

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