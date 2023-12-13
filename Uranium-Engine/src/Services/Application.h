#pragma once

#include <memory>
#include <vector>
#include <string>

namespace Uranium::Core {
	extern class BaseEngine;
}

namespace Uranium::Display {
	extern class MonitorHandler;
}

namespace Uranium::Services {

	class Application final {
	public:
		/*
		* Returns an instance of the application
		*/
		static Application& instance();

		/*
		* Returns a reference to the base engine
		*/
		Core::BaseEngine& getBaseEngine();

	private:
		/*
		* Unique application reference
		*/
		static Application* application;
		
		/*
		* Extern friend to start application
		* Located at: EntryPoint.cpp
		*/
		friend void buildApplication(int argc, char* argv[]);

		/*
		* Default method that logs any GL errors
		*/
		static void diagnosticErrors(int error, const char* description);
		
	private:
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
		* Initiates application
		*/
		void init() const;
		
		/*
		* Runs the application content
		*/
		void run();
		
		/*
		* Adds an argument from terminal when program starts
		*/
		void addArgument(const std::string& arg);

	private:
		// These are the passed arguments from terminal
		std::vector<std::string> arguments;

		// reference to the base engine
		std::unique_ptr<Core::BaseEngine> baseEngine;
	};
}