#pragma once

#include <memory>
#include <vector>
#include <string>

namespace Uranium::Services {

	class BaseEngine;

	class Application final {
	public:
		/*
		* Returns an instance of the application
		*/
		static Application& instance();

	private:
		/*
		* Unique application reference
		*/
		static std::unique_ptr<Application> application;
		
		/*
		* Extern friend to start application
		* Located at: EntryPoint.cpp
		*/
		friend void startApplication(int argc, char* argv[]);

		/*
		* Build the application at the default
		* entry point (main function).
		*/
		static void build(int argc, char* argv[], std::unique_ptr<BaseEngine> baseEngine);

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

	private:
		/*
		* Runs the application content
		*/
		void run();
		
		/*
		* Adds an argument from terminal when program starts
		*/
		void addArgument(const std::string& arg);

	private:
		std::vector<std::string> arguments;
		std::unique_ptr<BaseEngine> baseEngine;
	};
}