#pragma once

#include <memory>
#include <thread>

namespace Uranium::Display {
	extern class Window;
}

namespace Uranium::Services {

	class BaseEngine {
	private:
		/*
		* Friend with other classes
		*/
		friend class Application;

	public:
		/*
		* Constructor for initialization of the engine
		*/
		explicit BaseEngine() noexcept;

		virtual ~BaseEngine();

		/*
		* Delete the copy constructor,
		* because it doesn't make sense to
		* have more instances of a base engine.
		*/
		BaseEngine(BaseEngine&) = delete;
		BaseEngine(const BaseEngine&) = delete;

	protected:
		/*
		* Creates a window inside the context.
		* If the function returns nullptr, then
		* no window will be created inside this context
		* making it behave like a regular thread.
		*/
		virtual std::shared_ptr<Display::Window> createWindow() = 0;
	
		/*
		* Creates a set of scenes that influence the
		* flow of events inside the application.
		*/
		virtual std::shared_ptr<int> createScenes() = 0;

	private:
		/*
		* Starts the engine will all the contents
		*/
		void start();

	private:
		std::thread thread;
		std::shared_ptr<Display::Window> display;
		std::shared_ptr<int> scenes; // TEMP
	};
}