#pragma once

#include <memory>
#include <vector>
#include <string>

namespace Uranium::Engine {
	class BaseEngine;
}

namespace Uranium::Core {

	class Application final {
	public:
		~Application();

		/*
		* Deletes the copy/move constructors because
		* we dont want to accidently create instances or move
		* the application singleton
		*/
		Application(Application&) = delete;
		Application(Application&&) = delete;
		Application& operator=(const Application&) = delete;
		
	public:
		/*
		* Returns the instance of the currently active application
		*/
		static Application& instance();

		/*
		* Returns a reference of the base engine
		*/
		Engine::BaseEngine& getBaseEngine();

	private:
		/*
		* Creates a unique instance of application
		*/
		explicit Application() noexcept;

		/*
		* Starts the application
		*/
		void start() noexcept;

	private:
		/*
		* Holds a reference to the unique application instance
		* throughout the life time of the program
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
		std::vector<std::string> terminalArguments;

		std::unique_ptr<Engine::BaseEngine> baseEngine;
	};
}