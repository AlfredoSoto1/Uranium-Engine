#pragma once

#include "core/URAPI.h"
#include "WindowHND.h"

#include <vector>

namespace uranium::core {
	class Application;
}

namespace uranium::video::core {

	URANIUM_API enum class WindowError {

	};


	URANIUM_API class WindowManager final {
	public:
		/*
		* @brief
		* Using dependency injection, the window manager
		* before handling any resource related to a window context, 
		* it first has to load the application dependencies.
		* 
		* @param application
		*/
		WindowManager(uranium::core::Application& application) noexcept;
		~WindowManager() noexcept;

	public:
		/*
		* @brief
		* Initializes GLFW and all window default states.
		*/
		void init() noexcept;

		/*
		* @brief
		* Shutsdown GLFW and all window states.
		*/
		void shutdown() noexcept;

		/*
		* @brief
		* Kills all active window contexts.
		*/
		void killAll() noexcept;

		/*
		* @brief
		* Query all the errors that the window manager
		* caught durring initialization, preparation, runtime and shutdown.
		* 
		* @return list of errors
		*/
		std::vector<WindowError> queryErrors() noexcept;
	
	private:
		std::vector<WindowHND> windows;
		unsigned int activeWindowCount;
	};
}