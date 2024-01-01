#pragma once

#include <memory>
#include <vector>
#include <string>

namespace Uranium::Platform::Display {
	class Window;
}

namespace Uranium::Input::Events {
	class Event;
}

namespace Uranium::Core {

	class Application {
	public:
		/*
		* Creates and initializes a unique instance of the application
		*/
		explicit Application() noexcept;
		
		/*
		* Destroys and cleans up the application
		*/
		virtual ~Application();

		Application(Application&) = delete;
		Application(Application&&) = delete;
		Application& operator=(const Application&) = delete;

	public:
		static Application& instance() {
			return *application;
		}

		const Platform::Display::Window& getWindow() {
			return *windowDisplay;
		}
		
	protected:
		/*
		* Creates a unique instance of a window
		*/
		virtual std::unique_ptr<Platform::Display::Window> createWindow() = 0;

	private:
		/*
		* Holds a reference to the unique application instance
		* throughout the life time of the program
		*/
		static std::unique_ptr<Application> application;
		
		/*
		* Default method that logs any GL errors
		*/
		static void diagnosticErrors(int error, const char* description);
		
		/*
		* Extern friend to start application
		* Located at: EntryPoint.cpp
		*/
		friend void buildApplication(int argc, char* argv[]);

		/*
		* Starts the application
		*/
		void start() noexcept;

		void onEvent(Input::Events::Event& e);

	private:
		volatile bool isRunning;

		std::vector<std::string> terminalArguments;

		std::unique_ptr<Platform::Display::Window> windowDisplay;
	};
}