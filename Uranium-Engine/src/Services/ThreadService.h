#pragma once

#include <memory>
#include <thread>
#include "Services/Service.h"

namespace Uranium::Program {
	extern class Application;
}

namespace Uranium::Display {
	extern class Window;
}

namespace Uranium::Services {

	class ThreadService { // : public Services::Service {
	private:
		/*
		* Friend with other classes
		*/
		friend extern Program::Application;

	public:
		/*
		* Returns the number of active threads
		*/
		static volatile int activeThreadCount();

	private:
		/*
		* Count of active threads
		*/
		static volatile int threadCount;

	public:
		/*
		* This constructs a thread-context that references
		* a virtual thread for an OpenGL context-application
		*/
		explicit ThreadService() noexcept;

		virtual ~ThreadService();

		/*
		* Delete the copy constructor,
		* because we dont want more instances of
		* a thread that must be unique.
		*/
		ThreadService(ThreadService&) = delete;
		ThreadService(const ThreadService&) = delete;

	protected:
		/*
		* Creates a window inside the context.
		* If the function returns nullptr, then
		* no window will be created inside this context
		* making it behave like a regular thread.
		*/
		virtual std::shared_ptr<Display::Window> createWindow() = 0;
	
	private:
		/*
		* Overrided service methods
		*/
		void init();
		void start();
		void prune();

		bool isActive() const;

	private:
		volatile bool active;

		std::thread thread;
		std::shared_ptr<Display::Window> display;
	};
}