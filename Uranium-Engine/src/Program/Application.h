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
		template<class T, class... Args>
		explicit Application(T first, Args... args) noexcept :
			exitRequested(false),
			arguments(),
			contexts()
		{
			// These types of if statements that
			// serve to check conditions that should not
			// happen ever, need to be later in the future
			// turned into a macro so that in release this doesnt get evaluated
#ifdef UR_DEBUG
			if (instanceReference != nullptr)
				throw std::runtime_error("Instance of application already exists!");
#endif // _DEBUG

			// if the the application has not been created,
			// make it remember that an instance of it already exist
			instanceReference = this;

			// Emplace the unique reference to the context
			// as an rvalue first
			contexts.emplace_back(std::move(first));

			// Then emplace the rest of the references parameters
			(contexts.emplace_back(std::move(args)), ...);
		}

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