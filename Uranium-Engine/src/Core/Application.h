#pragma once

#include <memory>
#include <vector>
#include <string>

#include "CoreMacros.h"

namespace Uranium::Platform::Interface {
	//UR_DECLARE Window;
	//UR_DECLARE GraphicsAPI;
}

namespace Uranium::Input::Events {
	UR_DECLARE Event;
}

namespace Uranium::Core {

	URANIUM_API class Application {
	public:
		/*
		* @returns unique instance of application.
		*/
		static Application& instance();

	public:
		explicit Application() noexcept;
		virtual ~Application() noexcept = default;

		Application(Application&)  = delete;
		Application(Application&&) = delete;
		Application& operator=(const Application&) = delete;

	public:
		//using Window = Platform::Interface::Window;
		
	protected:
		/*
		* Creates a unique instance of a window
		* 
		* @return unique reference to window
		*/
		//virtual std::unique_ptr<Window> createWindow() = 0;

		/*
		* Creates the proper graphics API to use throught the Application.
		* You cannot change in run-time once having an API selected. If you
		* would like to change the API, the application must restart.
		*
		* @return unique reference to window
		*/
		//virtual std::unique_ptr<GraphicsAPI> prepareGraphicsAPI() = 0;

	private:
		/*
		* @brief Holds a reference to the unique application instance
		* throughout the life time of the program
		*/
		static std::unique_ptr<Application> application;

		/*
		* @brief Extern friend to start application
		* Located at: EntryPoint.cpp
		*/
		friend void buildApplication(int argc, char* argv[]);

	private:
		/*
		* Starts the application
		*/
		void start() noexcept;

		/*
		*/
		void onEvent(Input::Events::Event& e);

	private:
		//std::unique_ptr<Window> window;
		//std::unique_ptr<GraphicsAPI> graphicsAPI;
		
		volatile bool isRunning;
	};
}