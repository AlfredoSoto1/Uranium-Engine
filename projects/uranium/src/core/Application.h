#pragma once

#include "URAPI.h"

#include <vector>
#include <string>
#include <memory>

namespace uranium::core {

	URANIUM_API UR_ABSTRACT_CLASS Application {
	public:
		/*
		* @return unique application instance
		*/
		static Application& instance();

		/*
		* @brief
		* Starts the application
		* 
		* @param argument count
		* @param argument list reference
		* @param application reference
		*/
		static int start(int argc, char** argv, std::unique_ptr<Application> app_ref) noexcept;

	public:
		explicit Application() noexcept;
		virtual ~Application() = default;

		Application(Application&)  = delete;
		Application(Application&&) = delete;
		Application& operator=(const Application&) = delete;

	public:
		void interrupt() noexcept;
		void exit(int code) noexcept;
		
		std::vector<int> queryErrors() noexcept;

	protected:
		virtual void init()     noexcept = 0;
		virtual void shutdown() noexcept = 0;

		virtual void loadConfig() noexcept = 0;
		virtual void saveConfig() noexcept = 0;

	private:
		/*
		* @brief 
		* Holds a reference to the unique application instance
		* throughout the life time of the program
		*/
		static std::unique_ptr<Application> application;

	private:
		volatile bool isRunning;
	};
}