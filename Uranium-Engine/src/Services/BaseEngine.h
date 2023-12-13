#pragma once

#include <memory>
#include <thread>

namespace Uranium::Display {
	extern class Window;
}

namespace Uranium::Input::Callbacks {
	extern class WindowCallback;
	extern class MonitorCallback;
	extern class MouseCallback;
	extern class CursorCallback;
	extern class KeyboardCallback;
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

	public:
		/*
		* Returns a reference to window
		*/
		std::shared_ptr<Display::Window> getWindow() const;

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
		* Runs the engine
		*/
		void run();

		void createCallbacks();
		void disposeCallbacks();

	private:
		/*
		* Engine threads
		*/
		std::thread updateThread;
		std::thread renderingThread;
		
		std::shared_ptr<int> scenes; // TEMP
		std::shared_ptr<Display::Window> display;

		/*
		* Engine callbacks
		*/
		Input::Callbacks::MouseCallback*    mouseCallback;
		Input::Callbacks::CursorCallback*   cursorCallback;
		Input::Callbacks::WindowCallback*   windowCallback;
		Input::Callbacks::MonitorCallback*  monitorCallback;
		Input::Callbacks::KeyboardCallback* keyboardCallback;
	};
}