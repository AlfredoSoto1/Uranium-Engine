#pragma once

#include <memory>
#include <vector>
#include <string>

namespace Uranium::Services {
	extern class ThreadService;
}

namespace Uranium::Program {

	class Application final {
	public:
		/*
		* Return the Application instance from singleton
		*/
		static Application& instance();

	private:
		/*
		* Extern friend to start application
		* Located at: EntryPoint.cpp
		*/
		friend void startApplication(int argc, char* argv[]);

		/*
		* Unique static reference of the entire application
		*/
		static std::unique_ptr<Application> application;
		
		/*
		* Build the application at the default
		* entry point (main function).
		*/
		static void build(int argc, char* argv[], std::unique_ptr<Application> createdApplication);

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
		* Registers a new service reference to the application
		*/
		void registerService(std::unique_ptr<Services::ThreadService> service);

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
		/*
		* In-Terminal arguments
		*/
		std::vector<std::string> arguments;

		/*
		* Current registered services
		*/
		std::vector<std::unique_ptr<Services::ThreadService>> services;
	};
}