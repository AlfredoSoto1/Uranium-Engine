//#pragma once
//
//#include "URAPI.h"
//
//#include <vector>
//#include <string>
//#include <memory>
//
//namespace uranium::core {
//
//	URANIUM_API class Application {
//	public:
//		static Application& instance();
//
//		static int start(std::unique_ptr<Application> application);
//
//	public:
//		explicit Application() noexcept;
//		virtual ~Application() noexcept = default;
//
//		Application(Application&)  = delete;
//		Application(Application&&) = delete;
//		Application& operator=(const Application&) = delete;
//
//	protected:
//		/*
//		* Put virtual methods here
//		*/
//		
//	private:
//		void init()      noexcept;
//		void shutdown()  noexcept;
//		void interrupt() noexcept;
//		
//		void exit(int code) noexcept;
//
//		std::vector<int> queryErrors() noexcept;
//
//	private:
//		/*
//		* @brief 
//		* Holds a reference to the unique application instance
//		* throughout the life time of the program
//		*/
//		static std::unique_ptr<Application> application;
//
//	private:
//		volatile bool isRunning;
//	};
//}