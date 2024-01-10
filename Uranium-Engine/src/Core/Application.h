#pragma once

#include <memory>
#include <vector>
#include <string>
#include "CoreMacros.h"

namespace Uranium::Platform::Display {
	class Window;
}

namespace Uranium::Input::Events {
	class Event;
}

namespace Uranium::Core {

	URANIUM_API class Application {
	private:
		/*
		* Holds a reference to the unique application instance
		* throughout the life time of the program
		*/
		static std::unique_ptr<Application> application;

		/*
		* Extern friend to start application
		* Located at: EntryPoint.cpp
		*/
		friend void buildApplication(int argc, char* argv[]);

	public:
		explicit Application() noexcept;
		virtual ~Application() noexcept;

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
		* Starts the application
		*/
		void start() noexcept;

		/*
		*/
		void onEvent(Input::Events::Event& e);

	private:
		volatile bool isRunning;

		std::unique_ptr<Platform::Display::Window> windowDisplay;
	};
}