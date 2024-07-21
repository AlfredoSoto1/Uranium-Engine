#pragma once

#include "URAPI.h"

#include <vector>
#include <string>
#include <memory>

namespace uranium::core {

	URANIUM_API class Application {
	public:
		static Application& instance();

		static int start(std::unique_ptr<Application> application);

	public:
		explicit Application() noexcept;
		virtual ~Application() noexcept = default;

		Application(Application&)  = delete;
		Application(Application&&) = delete;
		Application& operator=(const Application&) = delete;

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
		void init()      noexcept;
		void shutdown()  noexcept;
		void interrupt() noexcept;
		
		void exit(int code) noexcept;

		std::vector<int> queryErrors() noexcept;

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
		friend void buildApplication();

	private:
		//std::unique_ptr<Window> window;
		//std::unique_ptr<GraphicsAPI> graphicsAPI;
		
		volatile bool isRunning;
	};
}